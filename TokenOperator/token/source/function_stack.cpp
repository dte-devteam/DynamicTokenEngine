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
	//TODO: push can overflow through stack_end
	blocks.emplace_back(
		blocks.back().physical_end, 
		blocks.back().physical_end + block_size
	);
}
void function_stack::push_virt(void* virt_block) {
	blocks.emplace_back(
		reinterpret_cast<char*>(virt_block),
		blocks.back().physical_end
	);
}
void function_stack::pop() {
	blocks.pop_back();
}
void function_stack::pop(size_t block_num) {
	blocks.pop_back(block_num);
}
void function_stack::clear() {
	pop(get_size());
}
size_t function_stack::get_size() const {
	return blocks.get_used_size() - 1; //- 1 because first is initial zero size block (never used)
}
void* function_stack::operator[](size_t index) const {
	return blocks[index + 1].virtual_begin;	//+ 1 because first is initial zero size block (never used)
}
