#ifndef INCLUDED_CHATQT_EXECUTORFACTORY_HPP
#define INCLUDED_CHATQT_EXECUTORFACTORY_HPP

#include <nlohmann/json.hpp>

#include "ConnectionSender.hpp"
#include "RequestFactory.hpp"
#include "Context.hpp"
#include "ExecutorTypes.hpp"
#include "Executor.hpp"
#include "Executors/ReceiveMessage.hpp"

class ExecutorFactory
{
public:
	ExecutorFactory(){};
	int create(ExecutorType type);
	int execute(const nlohmann::json &j_request, ConnectionSender *sender, Context *context, RequestFactory *factory);

	const std::shared_ptr<Executor> &getExecutor(unsigned int id);
	
private:
	unsigned int __next_id = 0;
	std::map<unsigned int, std::shared_ptr<Executor>> __executors;
};

#endif
