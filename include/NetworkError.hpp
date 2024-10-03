#ifndef INCLUDED_NETWORKERRORS_HPP
#define INCLUDED_NETWORKERRORS_HPP

#include <exception>
#include <string>

class NetworkError : public std::exception
{
public:
	NetworkError(const std::string &what_msg, int num = -1);
	const char *what()const noexcept;
	int no()const;

private:
	std::string __what_msg = "";
	int __errno = -1;
};

#endif
