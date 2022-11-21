#pragma once
#include <vector>
namespace memory {
	namespace table {
		struct typedesc {
			uint32_t type = 0;
			size_t size = 0;
		};
		struct streamheap {
			uint64_t id = 0;
			std::vector<void*> iterators;
		};
	}
}