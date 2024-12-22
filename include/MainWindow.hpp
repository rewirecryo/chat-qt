#ifndef INCLUDED_MAINWINDOW_HPP
#define INCLUDED_MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

#include "Connection.hpp"
#include "Licensing.hpp"
#include "RequestFactory.hpp"
#include "Requests/ForwardMessage.hpp"
#include <thread>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @param connection Connection to the server
	 * @param conn_thread Thread that connection is running
	 * @param parent
	 */
	MainWindow(Connection *connection, std::thread *conn_thread, Context *context, RequestFactory *request_factory, QWidget *parent = 0);

	virtual ~MainWindow();

	void startLoop();

	/**
	 * @brief Tell the user information about the licensing of chat-qt's dependencies.
	 */
	void displayLicenseInfo();
					
public slots:
	void submitMessage();

private:
	QPushButton *__button;
	QTextEdit *__messageLog;
	QLineEdit *__messageBox;
	QVBoxLayout *__mainLayout;
	QHBoxLayout *__rowLayout;

	Connection *__connection = nullptr;
	std::thread *__connectionThread = nullptr;
	bool __connected = false;
	bool __receiving = false;
	Context *__context = nullptr;
	RequestFactory *__request_factory = nullptr;
};

#endif
