#include "../../include/Executors/ReceiveMessage.hpp"

int exe::ReceiveMessage::execute(const nlohmann::json &j_instruction, ConnectionSender *sender, Context *context, RequestFactory *factory)
{
	__message_text = j_instruction["content"];
	if(context->user_list->userExists(j_instruction["sender"]))
	{
		__displayMessage(context->message_textedit, &context->user_list->getUser(j_instruction["sender"]));
	}
	else
	{
			__find_user_req = std::make_shared<ins::FindUser>(j_instruction["sender"]);
			__find_user_req->setParentID(getID());
			factory->add(__find_user_req);
			sender->sendRequest(__find_user_req);

			__sender_id = j_instruction["sender"];
	}
	return -1;
}

int exe::ReceiveMessage::continueExecution(ConnectionSender *sender, Context *context, RequestFactory *factory)
{
	nlohmann::json j_resp = __find_user_req->getResponse();
	if(j_resp["user_id"] != -1)
	{
		context->user_list->addUser(User(j_resp["user_id"], j_resp["username"]));
		__displayMessage(context->message_textedit, &context->user_list->getUser(j_resp["user_id"]));
	}

	return -1;
}

void exe::ReceiveMessage::__displayMessage(QTextEdit *text_area, User *user)
{
	text_area->append(QString::fromStdString(user->getUsername() + ": " + __message_text));
}
