#include "../include/UserList.hpp"

void UserList::addUser(const User &user)
{
	if(user.getID() < 0)
	{
		throw std::runtime_error("UserList::addUser(): Tried to create a user with an invalid ID.");
	}

	__users[user.getID()] = user;
}

void UserList::removeUser(unsigned int id)
{
	__users.erase(id);
}

User &UserList::getUser(unsigned int id)
{
	return __users.at(id);
}

bool UserList::userExists(unsigned int id)
{
	return __users.count(id) > 0;
}
