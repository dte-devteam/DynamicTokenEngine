#include "../include/initialization_data.h"
using namespace dte_utils;
using namespace dte_token;
namespace dte_core {
	bool call_dynamic_function(func_args& stack, const size_t stack_frame_begin) {
		if (stack.get_used_size() - stack_frame_begin) {
			const strong_ref<token, false>& func_ref = *stack.back();
			if (func_ref && func_ref.get_strong_owners()) {
				if (func_ref->d && func_ref->d.get_strong_owners()) {
					//to do: check if type is dynamic_function
					stack.pop_back();
					((dynamic_function*)func_ref->d.get_pointer())->execute(stack, stack.get_used_size() - stack_frame_begin);
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
		else {
			//error: function accepts at least 1 arg (dynamic_function handler and stack end)
		}
		//to do (which return should be)
		return false;
	}
	bool add(func_args& stack, const size_t stack_frame_begin) {
		if (get_function_frame_size(stack, stack_frame_begin) < 2) {
			throw; //need a & b
		}
		//*checking type and value handle*
		//std::cout << stack.get_used_size() << ":" << stack_frame_begin;
		*((int*)stack[stack_frame_begin]->d.get_pointer()) += *((int*)stack[stack_frame_begin + 1]->d.get_pointer());
		return false;
	}
}