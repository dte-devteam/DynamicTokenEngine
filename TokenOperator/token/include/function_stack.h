#pragma once
import memory;
import utils.dynamic_memory.dynamic_stack;
namespace dte_token {
	struct function_stack {
		struct block {
			char* virtual_begin;
			char* physical_end;
		};
		protected:
			dte_utils::dynamic_stack<block> blocks;
			char* stack_end;
		public:
			function_stack(size_t stack_size);
			~function_stack();
			void push_real(size_t block_size);
			void push_virt(void* virt_block);
			void pop();
			void pop(size_t block_num);
			void clear();
			size_t get_size() const;
			void* operator[](size_t index) const;

	};
}