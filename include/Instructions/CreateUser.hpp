#ifndef INCLUDED_CHATQT_INSTRUCTIONS_CREATEUSER
#define INCLUDED_CHATQT_INSTRUCTIONS_CREATEUSER

#include <nlohmann/json.hpp>

#include "../Instruction.hpp"

namespace ins
{
	class CreateUser : public Instruction
	{
	public:
		CreateUser();
		CreateUser(const std::string &new_username);

		nlohmann::json toJSON()const;
		
		void setUsername(const std::string &new_username);
		const std::string &getUsername()const;
		
	protected:
		std::string __username = "";
		const InstructionType __type = InstructionType::CREATE_USER;
	};
};
#endif
