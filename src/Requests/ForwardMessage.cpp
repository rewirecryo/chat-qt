#include "../../include/Requests/ForwardMessage.hpp"

ins::ForwardMessage::ForwardMessage()
{
	__setType(RequestType::FORWARD_MESSAGE);
}

ins::ForwardMessage::ForwardMessage(const std::string &text)
{
	__setType(RequestType::FORWARD_MESSAGE);
	setText(text);
}

nlohmann::json ins::ForwardMessage::toJSON()const
{
	nlohmann::json j_request = __jsonTemplate();

	j_request["msg_text"] = __text;
	
	return j_request;
}


void ins::ForwardMessage::setText(const std::string &text)
{
	__text = text;
}

const std::string &ins::ForwardMessage::getText()const
{
	return __text;
}

