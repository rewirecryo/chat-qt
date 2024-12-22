#include "../../include/Requests/CreateUser.hpp"

ins::CreateUser::CreateUser()
{
	__setType(RequestType::CREATE_USER);
}

ins::CreateUser::CreateUser(const std::string &new_username)
{
	__setType(RequestType::CREATE_USER);
	__username = new_username;
}

nlohmann::json ins::CreateUser::toJSON()const
{
	nlohmann::json j_request = __jsonTemplate();

	j_request["username"] = __username;

	return j_request;
}

void ins::CreateUser::setUsername(const std::string &new_username)
{
	__username = new_username;
}

const std::string &ins::CreateUser::getUsername()const
{
	return __username;
}
