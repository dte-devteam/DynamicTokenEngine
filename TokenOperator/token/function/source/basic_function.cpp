#include "token/function/include/basic_function.h"
using namespace tokenoperator::dte_token::function;
basic_function::basic_function(uint64_t ID, args defaultvalues) : object(ID), defaultvalues(defaultvalues) {}
void basic_function::form_argument(args* argumentspointer, args& target) const {
	if (argumentspointer) {
		size_t dv_size = defaultvalues.size();
		size_t a_size = argumentspointer->size();
		args arguments{a_size > dv_size ? a_size + 1 : dv_size + 1};
		size_t i = 0;
		while (i < a_size) {
			arguments[i++] = (*argumentspointer)[i];
		}
		while (i < dv_size) {
			arguments[i++] = defaultvalues[i];
		}
		target = arguments;
	}
	else {
		target = defaultvalues;
	}
}