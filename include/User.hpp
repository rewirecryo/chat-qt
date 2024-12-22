#ifndef INCLUDED_CHATQT_USER_HPP
#define INCLUDED_CHATQT_USER_HPP

#include <string>

class User
{
public:
	User();
	User(int new_id, const std::string &new_username);

	void setID(int new_id);
	int getID()const;

	void setUsername(const std::string &new_username);
	const std::string &getUsername()const;

private:
	int __id = -1;
	std::string __username = "";
};

#endif
