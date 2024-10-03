#include <nlohmann/json.hpp>
#include <iostream>
#include <signal.h>

#include <thread>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>

#include "../include/Server.hpp"
#include "../include/MainWindow.hpp"

#define ARGC_MIN 4

int main(int argc, char **argv)
{
	if(argc < ARGC_MIN)
	{
		std::clog << "Usage: chat <remote_address> <remote_port> <username>" << std::endl;
		return 1;
	}

	std::string remote_host(argv[1]), username(argv[3]);
	unsigned short port = std::stoi(argv[2]);

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
	std::thread msg_thread(&Connection::startReceivingMessages, &connection, 500);
	auto window = std::make_unique<MainWindow>(&connection, &msg_thread);
	window->show();

	return app.exec();
}
