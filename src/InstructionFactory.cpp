#include "../include/InstructionFactory.hpp"

std::shared_ptr<Instruction> InstructionFactory::create(InstructionType type)
{
	std::shared_ptr<Instruction> new_ins;

	switch(type)
	{
	case InstructionType::SEND_MESSAGE:
		new_ins = std::make_shared<ins::SendMessage>();
		break;
	case InstructionType::CREATE_USER:
		new_ins = std::make_shared<ins::CreateUser>();
		break;
	default:
		throw std::runtime_error("InstructionFactory::create(): Tried to create instruction with invalid type.");
	}

	int new_ins_id = __counter++;
	new_ins->setID(new_ins_id);
	__instructions[new_ins_id] = new_ins;

	return new_ins;
}
