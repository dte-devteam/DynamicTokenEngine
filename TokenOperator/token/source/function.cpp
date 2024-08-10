#include "../include/function.h"
using namespace dte_utils;
namespace dte_token {
	size_t get_function_frame_size(long_args& stack, const size_t stack_frame_begin) {
		return stack.get_used_size() - stack_frame_begin;
	}
	void clear_function_frame(long_args& stack, const size_t stack_frame_begin) {
		//stack.pop_back(get_function_frame_size(stack, stack_frame_begin));
	}
	void dynamic_function::execute(long_args& stack, const size_t stack_frame_begin) const {
		size_t i = 0;
		while (i < steps.get_used_size()) {
			const weak_ref<step_action>& act = steps[i].action;
			if (act && act.get_strong_owners()) {
				i += act(stack, stack_frame_begin, steps[i]);
			}
			else {
				//error: step is corrupted
				throw;
			}
		}
		//clear_function_frame(stack, stack_frame_begin);
	}
}