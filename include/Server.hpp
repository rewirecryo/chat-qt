#ifndef INCLUDED_SERVER_HPP
#define INCLUDED_SERVER_HPP

#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <QObject>

#include "Message.hpp"
#include "NetworkError.hpp"

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
	 * @brief Send a properly-formatted message to the server
	 * 
	 * @param msg - Message object whose contents to send
	 */
	void sendMessage(const Message &msg);

	/**
	 * @brief Call recv() and try to parse received data into a Message object
	 *
	 * @return Message object created from the data
	 */
	Message recvMessage();

	/**
	 * @brief Check if there's unread data from the server, by poll()ing the file descriptor
	 *
	 * @param timeout to pass to poll()
	 *
	 * @return True if there's unread data
	 */
	bool pollForMessage(int timeout);

	/**
	 * @return True if this connection is currently connected to a server
	 */
	bool isConnected()const;

	/**
	 * @brief Starts a while loop that checks for messages from the server and
	 *        emits the receivedMessage() signal upon receipt.
	 *
	 * @param timeout Timeout to pass to pollForMessage()
	 */
	void startReceivingMessages(int timeout);

	/**
	 * @brief Set __receiving to false. This is meant to stop the receiving
	 *        while-loop if it's been started in another thread.
	 */
	void stopReceivingMessages();
	
	/**
	 * @return True if the startReceivingMessages() loop is currently running
	 */
	bool isReceiving()const;

signals:

	/**
	 * @brief Emitted when we receive a message from the server
	 *
	 * @param text Emitted param
	 */
	void receivedMessage(const QString &text);
	
private:
	int  __socket_fd = -1;
	bool __connected = false;
	bool __receiving = false;
};

#endif
