#include "token/function/include/basic_function.h"
using namespace tokenoperator::dte_token::function;
basic_function::basic_function(uint64_t ID, bf_args defaultvalues) : object(ID), defaultvalues(defaultvalues) {}
bf_args basic_function::form_argument(bf_args* argumentspointer) const {
	if (argumentspointer) {
		size_t args_size = std::max(argumentspointer->get_size(), defaultvalues.get_size());
		bf_args arguments{args_size};
		object** target = arguments.get_data();
		
		//to do

		return arguments;
	}
	return defaultvalues;
}