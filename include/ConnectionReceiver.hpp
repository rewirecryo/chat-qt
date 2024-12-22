#ifndef INCLUDED_CHATQT_CONNECTIONRECEIVER_HPP
#define INCLUDED_CHATQT_CONNECTIONRECEIVER_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <sys/socket.h>

#include "NetworkError.hpp"

class ConnectionReceiver
{
public:
	ConnectionReceiver(int fd)
		: __socket_fd(fd){}
	
	nlohmann::json recvRequestList();
	
private:
	int __socket_fd = -1;
};

#endif
