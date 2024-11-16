#ifndef INCLUDED_CHATQT_INSTRUCTION_HPP
#define INCLUDED_CHATQT_INSTRUCTION_HPP

#include <nlohmann/json.hpp>

#include "InstructionTypes.hpp"

class Instruction
{
public:
	virtual nlohmann::json toJSON()const = 0;
	virtual void fromJSON(const nlohmann::json &src_json) = 0;

	InstructionType getType()const;

private:
	const InstructionType __type = InstructionType::UNKNOWN;
};

#endif
