#ifndef INCLUDED_MAINWINDOW_HPP
#define INCLUDED_MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

#include "Server.hpp"
#include "Licensing.hpp"
#include "Message.hpp"
#include "Instructions/SendMessage.hpp"
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
	MainWindow(Connection *connection, std::thread *conn_thread, QWidget *parent = 0);

	virtual ~MainWindow();

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
};

#endif
