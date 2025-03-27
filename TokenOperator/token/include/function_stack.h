#pragma once
import memory;
import utils.dynamic_memory.dynamic_array;
namespace dte_token {
	struct function_stack {
		struct block {
			char* end;
		};
		function_stack(size_t stack_size);
		~function_stack();
		dte_utils::dynamic_array<char*> blocks;
		char* stack_end;

		void push_real(size_t block_size);
		void push_virt(char* virt_block);
		void pop();
		void pop(size_t block_num);


	};
}