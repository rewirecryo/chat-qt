#include "../../include/Requests/FindUser.hpp"

ins::FindUser::FindUser()
{
	__setType(RequestType::FIND_USER);
}

ins::FindUser::FindUser(unsigned int user_id)
{
	__setType(RequestType::FIND_USER);
	__user_id = user_id;
}

nlohmann::json ins::FindUser::toJSON()const
{
	nlohmann::json j_request = __jsonTemplate();

	j_request["user_id"] = __user_id;

	return j_request;
}

void ins::FindUser::setUserID(unsigned int user_id)
{
	__user_id = user_id;
}

unsigned int ins::FindUser::getUserID()const
{
	return __user_id;
}
