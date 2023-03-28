#include "../include/basicfunction.h"
namespace function {
	basicfunction::basicfunction(uint64_t id, std::vector<void*> defaultvalues) : id(id), defaultvalues(defaultvalues) {}
	uint64_t basicfunction::getid() const {
		return id;
	}
	void basicfunction::filldefaultvalues(std::vector<void*>* argumentspointer, std::vector<void*> &target) {
		std::vector<void*> values(defaultvalues);
		if (!argumentspointer) {
			target = values;
			return;
		}
		size_t i = 0;
		size_t s = values.size();
		size_t argsize = argumentspointer->size();
		while (i < s && i < argsize) {
			values[i++] = (*argumentspointer)[i];
		}
		values.push_back(argumentspointer);
		target = values;
	}
}