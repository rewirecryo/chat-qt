#include "../include/Server.hpp"

void Connection::connect(const std::string &host, int port)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 6;

	struct addrinfo *retrieved_address;
	int ret = 0;
	if((ret = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &retrieved_address)) != 0)
	{
		throw NetworkError(gai_strerror(ret));
	}

	int sockfd;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}

	__socket_fd = sockfd;
		
	if(::connect(sockfd, retrieved_address->ai_addr, retrieved_address->ai_addrlen) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}

	__connected = true;
}

void Connection::disconnect()
{
	stopReceivingMessages();
	__connected = false;

	if(close(__socket_fd) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
}

void Connection::startReceivingMessages(int timeout)
{
	if(__connected == false)
	{
		throw NetworkError("Tried to call startReceivingMessages(), but not connected to a server.");
	}

	__receiving = true;
	while(__receiving == true)
	{
		// Check the server for a message
		try
		{
			if(pollForMessage(timeout))
			{
				emit receivedMessage(QString(recvMessage().text.c_str()));
			}
		}
		// This function is meant to run in a thread, and to be terminable by
		// setting __receiving false from outside the thread, which can
		// interrupt any network operation this function is doing. So, if we end
		// up getting network-related exception, we'll make sure to catch the
		// exception and _gracefully_ exit the loop.
		catch(const NetworkError &e)
		{
			__receiving = false;
			break;
		}
	}
}

void Connection::stopReceivingMessages()
{
	__receiving = false;
}

bool Connection::isConnected()const
{
	return __connected;
}

void Connection::sendMessage(const Message &msg)
{
	std::string jstr_msg_instructions = wrapInArray(msg.toJSON()).dump();
	if(send(__socket_fd, jstr_msg_instructions.c_str(), std::min<size_t>(jstr_msg_instructions.size(), 1023), 0) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
}

Message Connection::recvMessage()
{
	Message msg("");
	int ret;

	char buf[1024];

	if((ret = recv(__socket_fd, buf, 1023, 0)) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
	buf[ret] = '\0';

	nlohmann::json j_instructions = nlohmann::json::parse(std::string(buf));
	for(const nlohmann::json &j : j_instructions)
	{
		if(j["instruction_type"] == InstructionType::SEND_MESSAGE)
		{
			msg.text = std::string(j["msg_text"]);
		}
	}

	return msg;
}

bool Connection::pollForMessage(int timeout)
{
	struct pollfd pfd;
	pfd.fd = __socket_fd;
	pfd.events = POLLIN;
		
	switch(poll(&pfd, 1, timeout))
	{
	case -1:
		throw NetworkError(strerror(errno), errno);
		break;

	case 0:
		return false;
		break;
			
	default:
		return true;
		break;
	}
}

bool Connection::isReceiving()const
{
	return __receiving;
}
