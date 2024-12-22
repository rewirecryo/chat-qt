#include "../include/ExecutorFactory.hpp"

int ExecutorFactory::create(ExecutorType type)
{
	Executor *executor = nullptr;
	
	switch(type)
	{
	case ExecutorType::RECEIVE_MESSAGE:
		executor = new exe::ReceiveMessage();
		break;
	default:
		throw std::logic_error("ExecutorFactory::create(): Tried to create an invalid type of executor.");
	}

	unsigned int new_exe_id = __next_id++;
	executor->setID(new_exe_id);
	__executors[new_exe_id] = std::shared_ptr<Executor>(executor);
	return new_exe_id; 
}

int ExecutorFactory::execute(const nlohmann::json &j_request, ConnectionSender *sender, Context *context, RequestFactory *factory)
{
	auto find_result = __executors.find(j_request["request_type"]);
	if(find_result == __executors.end() || j_request["request_type"] == ExecutorType::UNKNOWN_EXECUTORTYPE)
	{
		throw std::out_of_range("ExecutorFactory::execute(): Tried to access an executor that doesn't exist.");
	}

	std::weak_ptr<Executor> executor_ptr = (*find_result).second;
	
	return executor_ptr.lock()->execute(j_request, sender, context, factory);
}

const std::shared_ptr<Executor> &ExecutorFactory::getExecutor(unsigned int id)
{
	return __executors[id];
}
