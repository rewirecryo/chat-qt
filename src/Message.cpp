#include "../include/Message.hpp"

Message::Message(const std::string &text_tmp)
{
	text = text_tmp;
}

nlohmann::json Message::toJSON()const
{
	nlohmann::json j;
	j["instruction_type"] = InstructionType::SEND_MESSAGE;
	j["msg_text"] = text;

	return j;
}
