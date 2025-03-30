#include "../include/function_stack.h"
#include <malloc.h>
using namespace dte_token;
using namespace dte_utils;
function_stack::function_stack(size_t stack_size) {
	char* begin = malloc_t<char>(stack_size);
	blocks.emplace_back(begin, begin);
	stack_end = begin + stack_size;
}
function_stack::~function_stack() {
	free(blocks[0].virtual_begin);
}
void function_stack::push_real(size_t block_size) {
	blocks.emplace_back(
		block(
			blocks.back().physical_end, 
			blocks.back().physical_end + block_size
		)
	);
}
void function_stack::push_virt(char* virt_block) {
	blocks.emplace_back(
		virt_block,
		blocks.back().physical_end
	);
}
void function_stack::pop() {
	blocks.pop_back();
}
void function_stack::pop(size_t block_num) {
	blocks.pop_back(block_num);
}