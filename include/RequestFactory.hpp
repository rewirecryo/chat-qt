#ifndef INCLUDED_CHATSERVER_REQUESTFACTORY_HPP
#define INCLUDED_CHATSERVER_REQUESTFACTORY_HPP

#include <memory>

#include "Request.hpp"
#include "Requests/ForwardMessage.hpp"
#include "Requests/CreateUser.hpp"
#include "Requests/FindUser.hpp"

class RequestFactory
{
public:
	int create(RequestType type);
	int add(std::shared_ptr<Request> ins);
	
	int fulfill(int request_id);

	void respondTo(int request_id, const nlohmann::json &j_response);

	int getParentIDOfRequest(int request_id)const;
	
private:
	void __add(int id, std::shared_ptr<Request> ins);
	
	int __next_id = 0;
	std::map<int, std::shared_ptr<Request>> __requests;
};

#endif
