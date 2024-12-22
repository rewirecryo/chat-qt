#ifndef INCLUDED_CHATQT_CONNECTIONSENDER_HPP
#define INCLUDED_CHATQT_CONNECTIONSENDER_HPP

#include <memory>
#include <sys/socket.h>

#include <nlohmann/json.hpp>

#include "NetworkError.hpp"
#include "Request.hpp"

class ConnectionSender
{
public:
	ConnectionSender(int fd);

	/**
	 * @brief Send a single request to the server
	 *
	 * @param request Request to send
	 */
	void sendRequest(std::shared_ptr<Request> request)const;

	/**
	 * @brief Send a list of requests to the server
	 * 
	 * @param request_list List of requests to send
	 */
	void sendRequestList(const std::vector<std::shared_ptr<Request>> &request_list)const;

private:
	int __socket_fd = -1;
};

#endif
