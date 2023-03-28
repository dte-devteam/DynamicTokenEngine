#include "../include/subtypedfunction.h"
namespace function {
	bool subtypedfunction::checktypecompability(std::vector<void*>* types) {
		for (size_t i = 0; i < types->size(); i++) {
			(*types)[i] = (void*)((size_t)(*types)[i] >> 32);
		}
		for (size_t i = 0; i < valuetypes.size(); i++) {
			for (void* arg : *types) {
				if (find_if(valuetypes[i].begin(), valuetypes[i].end(), [arg](void* value) { return value == arg; }) == valuetypes[i].end()) {
					return true;
				}
			}
		}
		return false;
	}
}