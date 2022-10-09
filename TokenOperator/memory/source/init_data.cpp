#include "../include/init_data.h"
#include <algorithm>
namespace memory {
	namespace init {
		void initbasefuncionstruct::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			for (void* value : defaultvalues) {
				std::vector<basicfunction*>::iterator iter = std::find_if(memory::function::functions.begin(), memory::function::functions.end(), [value](basicfunction* v) { return ((basicfunction*)value)->name == v->name; });
				if (iter == memory::function::functions.end()) {
					memory::function::functions.push_back((basicfunction*)value);
				}
				else if (forced) {
					delete *iter;
					*iter = (basicfunction*)value;
				}
			}
		}
	}
}