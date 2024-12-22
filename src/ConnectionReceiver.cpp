#include "../include/ConnectionReceiver.hpp"
#include <iostream>

nlohmann::json ConnectionReceiver::recvRequestList()
{
	char buf[1024];
	int ret = recv(__socket_fd, buf, 1023, 0);
	buf[ret] = '\0';

	if(ret == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
	else if(ret == 0) // If we lost the connection to the server, return a response to indicate that
	{
		nlohmann::json j_error;
		j_error["status"] = -1;
		j_error["requests"] = nlohmann::json();
		return j_error;
	}

	nlohmann::json j_requests = nlohmann::json::parse(std::string(buf));

	return j_requests;
}
