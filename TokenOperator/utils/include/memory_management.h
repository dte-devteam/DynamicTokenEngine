#pragma once
#include <malloc.h>
#include <cstddef>
namespace dte_utils {
	struct aligned_mem_block {
		static const size_t excess_bytes = sizeof(void*) < alignof(max_align_t) ? sizeof(void*) : alignof(max_align_t);;
		aligned_mem_block(size_t size, size_t alignment);
		~aligned_mem_block();
		void* get_real_pointer() const;
		void* get_virtual_pointer() const;
		void* expand(size_t size) const;
		void* realloc(size_t size);
		protected:
			void*	real_pointer;
			void*	virtual_pointer;
	};
}