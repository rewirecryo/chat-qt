#ifndef INCLUDED_SERVER_HPP
#define INCLUDED_SERVER_HPP

#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <QObject>

#include "NetworkError.hpp"
#include "Request.hpp"
#include "util.hpp"
#include "Context.hpp"
#include "ConnectionSender.hpp"
#include "ConnectionReceiver.hpp"

class Connection : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Connect to a server
	 */
	void connect(const std::string &host, int port);

	/**
	 * @brief Disconnect from the server you're connected to
	 */
	void disconnect();

	/**
	 * @brief Check if there's unread data from the server, by poll()ing the file descriptor
	 *
	 * @param timeout to pass to poll()
	 *
	 * @return True if there's unread data
	 */
	bool poll(int timeout);

	/**
	 * @return True if this connection is currently connected to a server
	 */
	bool isConnected()const;

	/**
	 * @brief Starts a while loop that checks for messages from the server and
	 *        emits the received() signal upon receipt.
	 *
	 * @param timeout Timeout to pass to this->poll()
	 */
	void startReceivingRequests(int timeout);

	/**
	 * @brief Set __receiving to false. This is meant to stop the receiving
	 *        while-loop if it's been started in another thread.
	 */
	void stopReceivingRequests();

	/**
	 * @return True if the startReceivingRequests() loop is currently running
	 */
	bool isReceiving()const;

	nlohmann::json recvRequestList();

	void sendRequest(std::shared_ptr<Request> request)const;

	const std::shared_ptr<ConnectionSender> &getSender()const;
	
signals:

	/**
	 * @brief Emitted when we receive an request from the server
	 *
	 * @param text Emitted param
	 */
	void receivedRequest(RequestType type, const nlohmann::json &j_request);

private:
	std::shared_ptr<ConnectionSender> __sender = nullptr;
	std::shared_ptr<ConnectionReceiver> __receiver = nullptr;
	int  __socket_fd = -1;
	bool __connected = false;
	bool __receiving = false;
	Context *__context = nullptr;
};

#endif
