#ifndef INCLUDED_CHATQT_USERLIST_HPP
#define INCLUDED_CHATQT_USERLIST_HPP

#include "User.hpp"
#include <map>
#include <stdexcept>

class UserList
{
public:
	void addUser(const User &user);
	void removeUser(unsigned int id);
	
	bool userExists(unsigned int id);
	
	User &getUser(unsigned int id);
	
private:
	std::map<unsigned int, User> __users;
};

#endif
