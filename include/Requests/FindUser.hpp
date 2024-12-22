#ifndef INCLUDED_CHATQT_REQUESTS_FINDUSER
#define INCLUDED_CHATQT_REQUESTS_FINDUSER

#include <nlohmann/json.hpp>

#include "../Request.hpp"

namespace ins
{
	class FindUser : public Request
	{
	public:
		FindUser();
		FindUser(unsigned int user_id);

		nlohmann::json toJSON()const;
		
		void setUserID(unsigned int user_id);
		unsigned int getUserID()const;

	protected:
		unsigned int __user_id;
		const RequestType __type = RequestType::FIND_USER;
	};
};
#endif
