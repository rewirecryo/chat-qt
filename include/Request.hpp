#ifndef INCLUDED_CHATQT_REQUEST_HPP
#define INCLUDED_CHATQT_REQUEST_HPP

#include <nlohmann/json.hpp>

#include "RequestTypes.hpp"

class Request
{
public:
	virtual nlohmann::json toJSON()const = 0;

	RequestType getType()const;

	void setID(int new_id);
	int getID()const;

	/**
	 * @brief Give a response to this request
	 */
	void setResponse(const nlohmann::json &j_response);
	const nlohmann::json &getResponse()const;

	bool hasResponse()const;

	void setParentID(int parent_id);
	int getParentID()const;
	
protected:
	/* This setter is protected because it should only be called by the object
	   itself. (One time, in the constructor.) */
	void __setType(RequestType type);
	nlohmann::json __jsonTemplate()const;
	
	int __id = -1;
	int __parent_id = -1;
	nlohmann::json __j_response;
	bool __has_response = false;
	RequestType __type = RequestType::UNKNOWN;
};

#endif
