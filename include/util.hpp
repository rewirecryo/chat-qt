#ifndef INCLUDED_CHATCLIENTQT_UTIL_HPP
#define INCLUDED_CHATCLIENTQT_UTIL_HPP

inline nlohmann::json wrapInArray(const nlohmann::json &j)
{
	return nlohmann::json({j});
}

#endif
