#include "../include/initialization_data.h"

#include <iostream>
using namespace dte_utils;
using namespace dte_token;
namespace dte_core {
	size_t call_static_function(long_args& stack, const size_t stack_frame_begin, const dynamic_function::function_step& step) {
		if (step.fa.func && step.fa.func.get_strong_owners()) {
			size_t new_stack_frame_begin = stack.get_used_size() - step.fa.overlap;
			size_t result = step.fa.func(stack, new_stack_frame_begin) ? step.fa.jump : 1;
			clear_function_frame(stack, new_stack_frame_begin);
			return result;
		}
		else {
			//error: function is corrupted
			throw;
		}
	}
	size_t call_dynamic_function(long_args& stack, const size_t stack_frame_begin, const dynamic_function::function_step& step) {
		const unknown_ref<token, false>& func_ref = step.va.fallback.pointer;
		if (func_ref && func_ref.get_strong_owners()) {
			if (func_ref->d && func_ref->d.get_strong_owners()) {
				//to do: check if type is dynamic_function
				((dynamic_function*)func_ref->d.get_pointer())->execute(stack, stack.get_used_size() - step.fa.overlap);
				return 1;
			}
			else {
				//error: value is not valid
				throw;
			}
		}
		else {
			//error: function is corrupted
			throw;
		}
	}
	size_t push_link(long_args& stack, const size_t stack_frame_begin, const dynamic_function::function_step& step) {
		//token::link* search = stack.find_ranged(
		//	[&step](const token::link& iter) { return step.va.search_name == iter.getcallname(); },
		//	stack_frame_begin,
		//	stack.get_used_size()
		//);
		//if (search) {
		//	search->pointer = step.va.fallback.pointer;
		//}
		//else {
		//std::cout << stack.get_used_size() << ":";
			stack.emplace_back(step.va.fallback.pointer, step.va.search_name);
		//}
		return 1;
	}





	bool add(long_args& stack, const size_t stack_frame_begin) {
		if (get_function_frame_size(stack, stack_frame_begin) < 2) {
			throw; //need a & b
		}
		//*checking type and value handle*
		//std::cout << stack.get_used_size() << ":" << stack_frame_begin;
		*((int*)stack[stack_frame_begin].pointer->d.get_pointer()) += *((int*)stack[stack_frame_begin + 1].pointer->d.get_pointer());
		return false;
	}
}