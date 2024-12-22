#include "../include/RequestFactory.hpp"

int RequestFactory::create(RequestType type)
{
	std::shared_ptr<Request> new_ins;

	switch(type)
	{
	case RequestType::FORWARD_MESSAGE:
		new_ins = std::make_shared<ins::ForwardMessage>();
		break;
	case RequestType::CREATE_USER:
		new_ins = std::make_shared<ins::CreateUser>();
		break;
	case RequestType::FIND_USER:
		new_ins = std::make_shared<ins::FindUser>();
		break;
	default:
		throw std::runtime_error("RequestFactory::create(): Tried to create request with invalid type.");
	}

	int new_ins_id = __next_id++;
	__add(new_ins_id, new_ins);
	return new_ins_id;
}

int RequestFactory::add(std::shared_ptr<Request> ins)
{
	int new_ins_id = __next_id++;
	__add(new_ins_id, ins);
	return new_ins_id;
}

void RequestFactory::__add(int id, std::shared_ptr<Request> ins)
{
	ins->setID(id);
	__requests[id] = ins;
}

int RequestFactory::fulfill(int request_id)
{
	int origin_executor_id = __requests[request_id]->getParentID();
	if(origin_executor_id == -1)
	{
		__requests.erase(request_id);
	}

	return origin_executor_id;
}

void RequestFactory::respondTo(int request_id, const nlohmann::json &j_response)
{
	auto find_ins = __requests.find(request_id);
	if(find_ins == __requests.end())
	{
		throw std::runtime_error("RequestFactory::respondTo(): Tried to respond to a Request that doesn't exist.");
	}

	((*find_ins).second)->setResponse(j_response);
}

int RequestFactory::getParentIDOfRequest(int request_id)const
{
	return __requests.at(request_id)->getParentID();
}
