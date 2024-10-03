#include "../include/NetworkError.hpp"

NetworkError::NetworkError(const std::string &what_msg, int errnum)
{
	__what_msg = what_msg;
	__errno = errnum;
}

const char *NetworkError::what()const noexcept
{
	return __what_msg.c_str();
}

int NetworkError::no()const
{
	return __errno;
}
