#include "../include/initialization_data.h"
using namespace dte_utils;
using namespace dte_token;
using namespace dte_core;
bool call_dynamic_function(long_args& stack, const size_t stack_frame_begin) {
	if (stack.get_used_size() < stack_frame_begin) {
		//error: no args provided
	}
	else {
		unknown_ref<token, false>& token_pointer = stack[stack_frame_begin].pointer;
		if (token_pointer && token_pointer.get_strong_owners()) {
			if (token_pointer->d && token_pointer->d.get_strong_owners()) {
				//to do: check if type is dynamic_function
				((dynamic_function*)token_pointer->d.get_pointer())->execute(stack, stack_frame_begin + 1);
			}
			else {
				//error: value is not valid
			}
		}
		else {
			//error: value is not handled
		}
	}
	return false;
}
bool set_rvalue(long_args& stack, const size_t stack_frame_begin) {
	//to do
	return false;
}
bool set_lvalue(long_args& stack, const size_t stack_frame_begin) {
	//to do
	return false;
}
bool clear_value(long_args& stack, const size_t stack_frame_begin) {
	//to do
	return false;
}