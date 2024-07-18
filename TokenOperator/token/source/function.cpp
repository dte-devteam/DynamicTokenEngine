#include "../include/function.h"
using namespace dte_token;
using namespace dte_utils;
bool funtion_literal::execute(long_args args) {
	//to do
	return false;
}
bool dll_function::execute(long_args args) {
	return fp(args);
}
bool dynamic_function::execute(long_args args) {
	size_t i = 0;
	while (i < functions.get_used_size()) {
		const weak_ref<function_call>& fc = functions[i].fc;
		if (fc && fc.get_strong_owners()) {
			i += fc->execute(long_args()) ? functions[i].jump : 1;
		}
		else {
			//error: stream is corrupted
		}
	}
	return true;
}