#include "../include/Instruction.hpp"

InstructionType Instruction::getType()const
{
	return __type;
}

void Instruction::setID(int new_id)
{
	__id = new_id;
}

int Instruction::getID()const
{
	return __id;
}
