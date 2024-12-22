#include "../include/User.hpp"

User::User(){}

User::User(int new_id, const std::string &new_username)
{
	__id = new_id;
	__username = new_username;
}

int User::getID()const
{
	return __id;
}

void User::setID(int new_id)
{
	__id = new_id;
}

const std::string &User::getUsername()const
{
	return __username;
}

void User::setUsername(const std::string &new_username)
{
	__username = new_username;
}
