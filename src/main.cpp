#include <nlohmann/json.hpp>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include <thread>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>

#include "../include/Connection.hpp"
#include "../include/ExecutorFactory.hpp"
#include "../include/MainWindow.hpp"
#include <chrono>

#define ARGC_MIN 4

static bool receiving = true;

inline int responseTo(const nlohmann::json &j)
{
	if(j.contains("response_to"))
	{
		return j["response_to"];
	}
	else
	{
		return -1;
	}
}

inline bool hasValidStatusCode(const nlohmann::json &j)
{
	return j["status"] == 0;
}

void runInstructionList(const nlohmann::json &j_instructions, ExecutorFactory *exe_factory, RequestFactory *req_factory, Context *context, ConnectionSender *sender)
{
	for(const nlohmann::json &j_current_ins : j_instructions)
	{
		// If the "Instruction" we received is actually a _Response_ to a
		// Request, let the Request object process that response.
		int response_to = responseTo(j_current_ins);
		if(response_to != -1)
		{
			// Forward the Response to the Request that invited it
			req_factory->respondTo(response_to, j_current_ins);

			// Sometimes, a request is sent from inside an executor. If that's
			// the case, the Executor will set itself as the Parent of the
			// Request.
			//
			// If the Response we just received was for a Request that was sent
			// from an executor, let the executor know.
			if(req_factory->getParentIDOfRequest(response_to) != -1)
			{
				exe_factory->getExecutor(req_factory->getParentIDOfRequest(response_to))->continueExecution(sender, context, req_factory);
			}
		}
		else
		{
			// Execute the request
			unsigned int new_exe_id = exe_factory->create(j_current_ins["instruction_type"]);
			std::shared_ptr<Executor> executor = exe_factory->getExecutor(new_exe_id);
			executor->execute(j_current_ins, sender, context, req_factory);
		}
	}

}

void startNetworkLoop(unsigned int timeout, Connection *conn, RequestFactory *req_factory, ExecutorFactory *exe_factory, Context *context, ConnectionSender *sender)
{
	// This loop should only be started if chat-qt is already connected to a chat-server instance
	if(conn->isConnected() == false)
	{
		throw NetworkError("Tried to call startNetworkLoop(), but not connected to a server.");
	}

	receiving = true; // Start receiving

	// Run this loop forever, until something tells us to stop
	while(receiving == true && conn->isConnected() == true)
	{
		try
		{
			// Only do anything if there's data on the wire
			if(conn->poll(timeout))
			{
				// 1) Read in the data on the wire as a blob
				// 2) Try to interpret it as an request list (in JSON), and turn it into a nlohmann::json object
				nlohmann::json j_request_list(conn->recvRequestList());

				// Make sure we're still connected (recvRequestList() will have set Connection::__connected to false if it couldn't reach chat-server)
				if(conn->isConnected() == true)
				{
					if(hasValidStatusCode(j_request_list)) // There's no point in processing anything if something went wrong server-side
					{
						runInstructionList(j_request_list["instruction_list"], exe_factory, req_factory, context, conn->getSender().get());
					}
				}
				else
				{
					receiving = false;
					break;
				}
			}
		}
		// This function is meant to run in a thread, and to be terminable by
		// setting __receiving false from outside the thread, which can
		// interrupt any network operation this function is doing. So, if we end
		// up getting network-related exception, we'll make sure to catch the
		// exception and _gracefully_ exit the loop.
		catch(const NetworkError &e)
		{
			receiving = false;
			break;
		}
	}
}

User createTheUser(const std::string &username, Connection *conn, RequestFactory *factory)
{
	// Create the request
	std::shared_ptr<ins::CreateUser> createuser_req = std::make_shared<ins::CreateUser>(); // Create the actual request
	createuser_req->setUsername(username); // The username we want the new user to have

	factory->add(createuser_req);
	conn->sendRequest(createuser_req);

	// Block until chat server's created the user
	while(!createuser_req->hasResponse())
	{
		sleep(1);
	}

	const nlohmann::json &j_response = createuser_req->getResponse();
	User user;
	user.setID(j_response["user_id"]);
	return user;
}

int main(int argc, char **argv)
{
	if(argc < ARGC_MIN)
	{
		std::clog << "Usage: chat <remote_address> <remote_port> <username>" << std::endl;
		return 1;
	}

	// Handle the cmdline arguments
	std::string remote_host(argv[1]), username(argv[3]);
	unsigned short port = std::stoi(argv[2]);

	std::shared_ptr<RequestFactory> request_factory = std::make_shared<RequestFactory>();
	std::shared_ptr<ExecutorFactory> executor_factory = std::make_shared<ExecutorFactory>();
	
	std::unique_ptr<Context> context = std::make_unique<Context>();
	context->user_list = std::make_shared<UserList>();

	Connection connection;
	try
	{
		connection.connect(remote_host, port);
	}
	catch(const NetworkError &e)
	{
		std::cerr << "Failed to connect." << std::endl;
		return 1;
	}

	QApplication app(argc, argv);

	// Start the thread that receives Requests from the server
	std::thread network_loop_thread(&startNetworkLoop, 500, &connection, request_factory.get(), executor_factory.get(), context.get(), connection.getSender().get());

	// Create the user chat-qt will log in as
	User user = createTheUser(username, &connection, request_factory.get());

	// Create the main window
	std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>(&connection, &network_loop_thread, context.get(), request_factory.get());
	window->show();
	
	return app.exec();
}
