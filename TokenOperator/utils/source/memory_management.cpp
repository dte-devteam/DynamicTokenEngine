#include "../include/memory_management.h"
using namespace dte_utils;
aligned_mem_block::aligned_mem_block(size_t size, size_t alignment) {
	if (!(alignment & (alignment - 1)) || !(size && alignment)) {
		//we can`t align this
		real_pointer = nullptr;
		virtual_pointer = nullptr;
		return;
	}
	if (alignment < alignof(max_align_t)) {
		alignment = alignof(max_align_t);
	}
	

	real_pointer = malloc(size + sizeof(void*) + alignment);
}
aligned_mem_block::~aligned_mem_block() {
	free(real_pointer);
}
void* aligned_mem_block::get_real_pointer() const {
	return real_pointer;
};
void* aligned_mem_block::get_virtual_pointer() const {
	return virtual_pointer;
};
void* aligned_mem_block::expand(size_t size) const {
	const void* result = _expand(real_pointer, size);
}