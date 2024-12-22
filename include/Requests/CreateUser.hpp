#ifndef INCLUDED_CHATQT_REQUESTS_CREATEUSER
#define INCLUDED_CHATQT_REQUESTS_CREATEUSER

#include <nlohmann/json.hpp>

#include "../Request.hpp"

namespace ins
{
	class CreateUser : public Request
	{
	public:
		CreateUser();
		CreateUser(const std::string &new_username);

		nlohmann::json toJSON()const;
		
		void setUsername(const std::string &new_username);
		const std::string &getUsername()const;

	protected:
		nlohmann::json __j_response;
		std::string __username = "";
	};
};
#endif
