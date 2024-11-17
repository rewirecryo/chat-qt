#ifndef INCLUDED_CHATQT_INSTRUCTION_HPP
#define INCLUDED_CHATQT_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

#include "InstructionTypes.hpp"

class Instruction
{
public:
	virtual nlohmann::json toJSON()const = 0;

	InstructionType getType()const;

protected:
	const InstructionType __type = InstructionType::UNKNOWN;
};

#endif
