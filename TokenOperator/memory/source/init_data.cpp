#include "../include/init_data.h"
#include <algorithm>
namespace memory {
	namespace init {
		void initbasefuncionstruct::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (errorcodepointer && !forced) {
				return;
			}
			for (void* value : defaultvalues) {
				std::vector<basicfunction*>::iterator iter = std::find_if(memory::function::functions.begin(), memory::function::functions.end(), [value](basicfunction* v) { return ((basicfunction*)value)->getid() == v->getid(); });
				if (iter == memory::function::functions.end()) {
					memory::function::functions.push_back((basicfunction*)value);
				}
				else if (forced) {
					delete *iter;
					*iter = (basicfunction*)value;
				}
			}
		}
		void initmemorystruct::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (argumentspointer->size() % 2) {
				if (!forced) {
					if (errorcodepointer) {
						*errorcodepointer = 8576;	//errorcode (change): can`t make pairs from not even argument count
					}
					return;
				}
			}
			std::vector<void*>::iterator end = argumentspointer->end();
			std::vector<void*>::iterator begin = argumentspointer->begin();
			std::vector<void*>::iterator i1 = begin;
			std::vector<void*>::iterator i2 = i1 + 1;
			while (!(i1++ == end || i2++ == end)) {
				memory::object::memorycontroller::instance()->addtypeallocator((size_t)*i1, (size_t)*i2);
			}
		}
	}
}