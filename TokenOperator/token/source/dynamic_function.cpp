#include "../include/dynamic_function.h"
using namespace dte_token;
using namespace dte_utils;
bool dynamic_function::execute(function_stack& stack, const size_t frame_offset) {
	size_t i = 0;
	
	while (i < steps.get_used_size()) {
		const bool& data_alive = steps[i].literal.get_pointer();
		const bool& func_alive = steps[i].f.get_strong_owners();
		if (data_alive) {
			char*& data_start = steps[i].literal->data_begin;
			if (func_alive) {
				//PUSH_REAL(const T& copy)
				std::cout << "AAA";
				stack.push_real(steps[i].literal->data_end - data_start);
				stack.push_virt(data_start);	//provide pointer to real value
				i = steps[i].f(stack, frame_offset + steps[i].block_offset) ? steps[i].jump_index : i + 1;
				stack.pop();					//remove virtual address
			}
			else {
				//PUSH_VIRT(T& sharing)
				std::cout << "BBB";
				stack.push_virt(data_start);
				i = steps[i].jump_index;
			}
		}
		else {
			if (func_alive) {
				//EXECUTE
				std::cout << "CCC";
				i = steps[i].f(stack, frame_offset + steps[i].block_offset) ? steps[i].jump_index : i + 1;
				//steps[i].f(stack, frame_offset + steps[i].block_offset);
			}
			else {
				//POP
				std::cout << "DDD";
				stack.pop(steps[i].block_offset);
				i = steps[i].jump_index;
			}
		}
	}
	return false;
}
