#ifndef INCLUDED_MESSAGE_HPP 
#define INCLUDED_MESSAGE_HPP

#include <nlohmann/json.hpp>

class Message
{
public:
	/**
	 * @param text_tmp Text 
	 */
	Message(const std::string &text_tmp);

	/**
	 * @brief Serialize to JSON
	 *
	 * @return JSON object
	 */
	nlohmann::json toJSON()const;

	std::string text = "";
};

#endif
