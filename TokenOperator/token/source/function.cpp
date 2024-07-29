#include "../include/function.h"
using namespace dte_token;
using namespace dte_utils;
void clear_function_frame(long_args& stack, const size_t stack_frame_begin) {
	stack.pop_back(stack.get_used_size() - stack_frame_begin);
}
void dynamic_function::execute(long_args& stack, const size_t stack_frame_begin) const {
	size_t i = 0;
	size_t stack_frame_end = stack_frame_begin + stack_frame_size;
	while (i < functions.get_used_size()) {
		const weak_ref<function>& fc = functions[i].fc;
		if (fc && fc.get_strong_owners()) {
			//to do fill stack
			i += fc(stack, stack_frame_end) ? functions[i].jump : 1;
			clear_function_frame(stack, stack_frame_end);
		}
		else {
			//error: function is corrupted
		}
	}
}