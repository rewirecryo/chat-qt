#ifndef INCLUDED_CHATQT_CONTEXT_HPP
#define INCLUDED_CHATQT_CONTEXT_HPP

#include "User.hpp"
#include <QTextEdit>
#include "UserList.hpp"
class Context
{
public:
	std::shared_ptr<UserList> user_list = nullptr;
	QTextEdit *message_textedit = nullptr;
};

#endif
