#include "../../include/Instructions/SendMessage.hpp"

ins::SendMessage::SendMessage()
{
}

ins::SendMessage::SendMessage(std::shared_ptr<Message> src_msg)
{
	__src_message = src_msg;
}

nlohmann::json ins::SendMessage::toJSON()const
{
	nlohmann::json new_json;
	new_json["id"] = __id;
	new_json["instruction_type"] = __type;
	new_json["msg_text"] = __src_message->text;
	
	return new_json;
}
