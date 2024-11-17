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
				Message msg = recvMessage();

				if(__connected)
				{
					emit receivedMessage(QString(msg.text.c_str()));
				}
				else
				{
					stopReceivingMessages();
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

void Connection::sendInstruction(std::shared_ptr<Instruction> instruction)
{
	sendInstructionList({instruction});
}

void Connection::sendInstructionList(const std::vector<std::shared_ptr<Instruction>> &instruction_list)
{
	nlohmann::json j_instruction_list = {};
	for(const std::shared_ptr<Instruction> &j_instruction : instruction_list)
	{
		j_instruction_list.push_back(j_instruction->toJSON());
	}

	std::string j_il_str = j_instruction_list.dump();
	if(send(__socket_fd, j_il_str.c_str(), std::min<size_t>(j_il_str.size(), 1023), 0) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
}

Message Connection::recvMessage()
{
	Message msg("");

	char buf[1024];
	int ret = recv(__socket_fd, buf, 1023, 0);

	if(ret == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
	else if(ret == 0)
	{
		__connected = false;
		return msg;
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
		if((pfd.revents & POLLERR) > 0)
		{
			throw NetworkError("poll() call returned an error.");
		}
		else
		{
			std::cerr << "Returned events: " << pfd.revents << " (POLLIN is code " << POLLIN << ")" << std::endl;
			return (pfd.revents == POLLIN);
		}
		break;
	}
}

bool Connection::isReceiving()const
{
	return __receiving;
}
