#include "../include/MainWindow.hpp"

MainWindow::MainWindow(Connection *connection, std::thread *conn_thread, QWidget *parent)
{
	__connectionThread = conn_thread;
	__connection = connection;

	__messageLog = new QTextEdit();
	__messageLog->setReadOnly(true);
	
	__messageBox = new QLineEdit();

	__button = new QPushButton("Send Message");

	__mainLayout = new QVBoxLayout(this);
	
	__rowLayout = new QHBoxLayout();
	__rowLayout->addWidget(__messageBox);
	__rowLayout->addWidget(__button);

	__mainLayout->addWidget(__messageLog);
	__mainLayout->addLayout(__rowLayout);
	__messageBox->setFocus();

	connect(__button, SIGNAL(clicked()), this, SLOT(submitMessage()));
	connect(__messageBox, SIGNAL(returnPressed()), this, SLOT(submitMessage()));
	connect(__connection, SIGNAL(receivedMessage(const QString&)), __messageLog, SLOT(append(const QString&)));

	__messageLog->setTextColor(QColor(0,0,255));
	__messageLog->append("This project uses the Qt 6 framework, which is licensed under version 3 of the GNU Lesser General Public License (LGPL).");
	__messageLog->append("To view a copy of the LGPL in this program, type the '/lgpl' command into the message box.");
	__messageLog->append("Repository: https://code.qt.io/qt/qt5.git");
	__messageLog->append("Website: https://www.qt.io/");
	__messageLog->append("License URL: https://www.gnu.org/licenses/lgpl-3.0.en.html");
	__messageLog->append("\n--\n");

	__messageLog->append("This project uses the JSON for Modern C++ library, which is licensed under the MIT License.");
	__messageLog->append("Repository: https://github.com/nlohmann/json");
	__messageLog->append("Website: https://json.nlohmann.me/");
	__messageLog->append("License URL: https://github.com/nlohmann/json/raw/refs/heads/develop/LICENSE.MIT");
	__messageLog->append("");

	__messageLog->setTextColor(QColor(0,0,0));
}

void MainWindow::submitMessage()
{
	if(__messageBox->text().size() == 0)
		return;

	/* Sloppy, tentative solution for printing LGPL to user. Qt requires us to
	   "provid[e] a copy of the LGPL license text to the user," and this is my
	   way of doing it.

	   https://www.qt.io/licensing/open-source-lgpl-obligations#lgpl
	*/
	if(__messageBox->text().size() >= 5)
	{
		if(__messageBox->text().toStdString().substr(0, 5) == "/lgpl")
		{
			__messageLog->append(LGPL3_TEXT);
			__messageLog->append("");
			__messageBox->clear();
			return;
		}
	}

	std::shared_ptr<Message> msg(new Message(__messageBox->text().toStdString()));
	std::shared_ptr<Instruction> instruction = std::make_shared<ins::SendMessage>(msg);
	__connection->sendInstruction(instruction);
	__messageBox->clear();
}

MainWindow::~MainWindow()
{
	if(__connection->isConnected())
	{
		__connection->disconnect();
	}
	__connection->stopReceivingMessages();
	__connectionThread->join();
}
