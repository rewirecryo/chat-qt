#ifndef INCLUDED_CHATQT_EXECUTORS_RECEIVEMESSAGE_HPP
#define INCLUDED_CHATQT_EXECUTORS_RECEIVEMESSAGE_HPP

#include <QTextEdit>

#include "../Executor.hpp"

namespace exe
{
	class ReceiveMessage : public Executor
	{
	public:
		int execute(const nlohmann::json &j_request, ConnectionSender *sender, Context *context, RequestFactory *factory);
		int continueExecution(ConnectionSender *sender, Context *context, RequestFactory *factory);

	private:
		void __displayMessage(QTextEdit *text_edit, User *user);

		std::string __message_text = "";
		int __sender_id = -1;
	
		int __state = 0;
		std::shared_ptr<Request> __find_user_req = nullptr;
	};
}
#endif
