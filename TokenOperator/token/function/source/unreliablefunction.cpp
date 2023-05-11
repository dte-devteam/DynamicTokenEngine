#include "../include/unreliablefunction.h"
namespace function {
	void unreliablefunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		if (errorcodepointer) {
			if (*errorcodepointer == 1) {
				callfunctions(values, errorcodepointer, true, stream);
			}
			else if (*errorcodepointer == 0) {
				//to do
				//clone data
				*errorcodepointer = 1;
				callfunctions(values, errorcodepointer, true, stream);
				//to do
				//write from clone to data
			}
		}
		else {
			callfunctions(values, errorcodepointer, forced, stream);
		}
	}
}