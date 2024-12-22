#include "../include/Request.hpp"

void Request::__setType(RequestType type)
{
	__type = type;
}

RequestType Request::getType()const
{
	return __type;
}

void Request::setID(int new_id)
{
	__id = new_id;
}

int Request::getID()const
{
	return __id;
}

void Request::setResponse(const nlohmann::json &j_response)
{
	__j_response = j_response;
	__has_response = true;
}

const nlohmann::json &Request::getResponse()const
{
	return __j_response;
}

bool Request::hasResponse()const
{
	return __has_response;
}

void Request::setParentID(int parent_id)
{
	__parent_id = parent_id;
}

int Request::getParentID()const
{
	return __parent_id;
}

nlohmann::json Request::__jsonTemplate()const
{
	nlohmann::json j_request_new;

	j_request_new["id"] = getID();
	j_request_new["request_type"] = getType();

	return j_request_new;
}
