#include "token/function/include/basicfunction.h"
using namespace tokenoperator::token::function;
basicfunction::basicfunction(uint64_t ID, args defaultvalues) : object(ID), defaultvalues{defaultvalues} {}
void basicfunction::formargument(args* argumentspointer, args& target) {
	if (argumentspointer) {
		size_t dv_size = defaultvalues.size();
		size_t a_size = argumentspointer->size();
		args arguments{a_size > dv_size ? a_size + 1 : dv_size + 1};
		size_t i = 0;
		while (i++ < a_size) {
			arguments[i] = (*argumentspointer)[i];
		}
		while (i++ < dv_size) {
			arguments[i] = defaultvalues[i];
		}
		target = arguments;
	}
	else {
		target = defaultvalues;
	}
}