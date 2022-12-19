#pragma once
#include <vector>
namespace memory {
	namespace table {
		//structures with data
		struct typedesc {
			uint32_t type = 0;
			size_t size = 0;
		};
		struct streamheap {
			uint64_t id = 0;
			std::vector<void*> iterators;
		};
		//stored data

		//make class of it
		inline std::vector<typedesc> type_table;
		inline bool registernewtype(uint32_t type, size_t size) {
			std::vector<typedesc>::iterator it = std::find_if(
				type_table.begin(),
				type_table.end(),
				[type](typedesc td) {
					return type == td.type;
				}
			);
			if (it == type_table.end()) {
				type_table.push_back(typedesc{ type, size });
				return true;
			}
			return false;
		}
	}
}