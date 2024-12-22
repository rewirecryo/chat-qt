#ifndef INCLUDED_CHATQT_REQUESTS_FORWARDMESSAGE
#define INCLUDED_CHATQT_REQUESTS_FORWARDMESSAGE

#include "../Request.hpp"
#include <iostream>

namespace ins
{
	class ForwardMessage : public Request
	{
	public:
		ForwardMessage();
		ForwardMessage(const std::string &text);

		nlohmann::json toJSON()const;

		void setText(const std::string &text);
		const std::string &getText()const;

	protected:
		/* Message that will be sent */
		std::string __text = "";
		const RequestType __type = RequestType::FORWARD_MESSAGE;
	};
};

#endif
