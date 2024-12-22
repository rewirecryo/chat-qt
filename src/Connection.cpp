#include "../include/Connection.hpp"

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

	__sender = std::make_unique<ConnectionSender>(__socket_fd);
	__receiver = std::make_unique<ConnectionReceiver>(__socket_fd);

	__connected = true;
}

void Connection::disconnect()
{
	__connected = false;

	if(close(__socket_fd) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
}

bool Connection::isConnected()const
{
	return __connected;
}

bool Connection::poll(int timeout)
{
	struct pollfd pfd;
	pfd.fd = __socket_fd;
	pfd.events = POLLIN;

	switch(::poll(&pfd, 1, timeout))
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
			throw NetworkError("Connection::poll: poll() syscall returned an error.");
		}
		else
		{
			return (pfd.revents == POLLIN);
		}
		break;
	}
}

bool Connection::isReceiving()const
{
	return __receiving;
}

nlohmann::json Connection::recvRequestList()
{
	return __receiver->recvRequestList();
}

void Connection::sendRequest(std::shared_ptr<Request> req)const
{
	__sender->sendRequest(req);
}

const std::shared_ptr<ConnectionSender> &Connection::getSender()const
{
	return __sender;
}
