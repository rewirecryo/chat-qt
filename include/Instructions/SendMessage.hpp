#ifndef INCLUDED_CHATQT_INSTRUCTIONS_SENDMESSAGE
#define INCLUDED_CHATQT_INSTRUCTIONS_SENDMESSAGE

#include "../Instruction.hpp"
#include "../Message.hpp"
#include <iostream>

namespace ins
{
	class SendMessage : public Instruction
	{
	public:
		SendMessage();
		SendMessage(std::shared_ptr<Message> src_msg);

		nlohmann::json toJSON()const;

	protected:
		/* Message that will be sent */
		std::shared_ptr<Message> __src_message = nullptr;
		const InstructionType __type = InstructionType::SEND_MESSAGE;
	};
};

#endif
