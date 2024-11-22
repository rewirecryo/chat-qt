#ifndef INCLUDED_CHATQT_INSTRUCTION_HPP
#define INCLUDED_CHATQT_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

#include "InstructionTypes.hpp"

class Instruction
{
public:
	virtual nlohmann::json toJSON()const = 0;

	InstructionType getType()const;

	void setID(int new_id);
	int getID()const;

protected:
	int __id = -1;

	const InstructionType __type = InstructionType::UNKNOWN;
};

#endif
