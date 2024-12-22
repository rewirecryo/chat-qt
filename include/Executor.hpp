#ifndef INCLUDED_CHATQT_EXECUTOR_HPP
#define INCLUDED_CHATQT_EXECUTOR_HPP

#include <nlohmann/json.hpp>

#include "Context.hpp"
#include "Connection.hpp"
#include "RequestFactory.hpp"

class Executor
{
public:
	Executor(){};
	virtual int execute(const nlohmann::json &j_request, ConnectionSender *sender, Context *context, RequestFactory *factory) = 0;
	virtual int continueExecution(ConnectionSender *sender, Context *context, RequestFactory *factory){ return -1; }

	void setID(int id);
	int getID()const;
	
protected:
	int __id = -1;
	
};

#endif
