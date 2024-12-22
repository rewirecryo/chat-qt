#include "../include/ConnectionSender.hpp"

ConnectionSender::ConnectionSender(int fd)
{
	__socket_fd = fd;
}

void ConnectionSender::sendRequest(std::shared_ptr<Request> request)const
{
	sendRequestList({request});
}

void ConnectionSender::sendRequestList(const std::vector<std::shared_ptr<Request>> &request_list)const
{
	nlohmann::json j_request_list = {};
	for(const std::shared_ptr<Request> &j_request : request_list)
	{
		j_request_list.push_back(j_request->toJSON());
	}

	nlohmann::json j_request;
	j_request["status"] = 0;
	j_request["instruction_list"] = j_request_list;
	std::string j_request_str = j_request.dump();
	if(send(__socket_fd, j_request_str.c_str(), std::min<size_t>(j_request_str.size(), 1023), 0) == -1)
	{
		throw NetworkError(strerror(errno), errno);
	}
}
