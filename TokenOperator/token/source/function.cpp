#include "../include/function.h"
using namespace dte_utils;
namespace dte_token {
	size_t get_function_frame_size(func_args& stack, const size_t stack_frame_begin) {
		return stack.get_used_size() - stack_frame_begin;
	}
	void clear_function_frame(func_args& stack, const size_t stack_frame_begin) {
		stack.pop_back(get_function_frame_size(stack, stack_frame_begin));
	}
	void dynamic_function::execute(func_args& stack, const size_t stack_frame_begin) const {
		size_t i = 0;
		while (i < steps.get_used_size()) {
			if (steps[i].func) {
				//do function
				if (steps[i].func.get_strong_owners()) {
					if (steps[i].func(stack, stack_frame_begin + steps[i].frame_offset)) {
						i = steps[i].index;
					}
					else {
						++i;
					}
				}
				else {
					//error: function is unloaded 
				}
			}
			else if (steps[i].literal) {
				//push pointer of data
				stack.push_back(steps[i].literal);
				++i;
			}
			else if (steps[i].index == SIZE_MAX) {
				//pop stack to frame_offset size
				clear_function_frame(stack, stack_frame_begin + steps[i].frame_offset);
				++i;
			}
			else {
				//push pointer of stack[index]
				stack.push_back(stack[steps[i].index]);
				++i;
			}
		}
	}
}