#include "../include/function_stack.h"
#include <malloc.h>
using namespace dte_token;
using namespace dte_utils;
function_stack::function_stack(size_t stack_size) {
	char* begin = malloc_t<char>(stack_size);
	blocks.emplace_back(begin);
	stack_end = begin + stack_size;
}
function_stack::~function_stack() {
	free((void*)blocks[0]);
}
void function_stack::push_real(size_t block_size) {
	blocks.push_back(blocks.back() + block_size);
}
void function_stack::push_virt(char* virt_block) {
	blocks.push_back(virt_block);
}
void function_stack::pop() {
	blocks.pop_back();
}
void function_stack::pop(size_t block_num) {
	blocks.pop_back(block_num);
}