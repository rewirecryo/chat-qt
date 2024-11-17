#include "../../include/Instructions/CreateUser.hpp"

ins::CreateUser::CreateUser(const std::string &new_username)
{
	__username = new_username;
}

nlohmann::json ins::CreateUser::toJSON()const
{
	nlohmann::json j;
	j["instruction_type"] = __type;
	j["username"] = __username;
	
	return j;
}

void ins::CreateUser::setUsername(const std::string &new_username)
{
	__username = new_username;
}

const std::string &ins::CreateUser::getUsername()const
{
	return __username;
}
