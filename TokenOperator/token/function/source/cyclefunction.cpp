#include "../include/cyclefunction.h"
namespace function {
	void cyclefunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		//note: pushes back data pointer, new pointer is bool*, so available index++ for callings args
		//advice: for use wrap your functions in construction {function(bool controller, trigger), triggeredfunction{any functions}}, but you can ignore this and use any fucntion combination
		//note: to stop cycle set cycletrigger to false or raise error, cycle will be executing forever if this condition is false
		//advice: for preventing eternal cycles, make threads or raise error in cycle (by iteration number or delta time)
		bool cycletrigger = true;
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		values.push_back(&cycletrigger);
		while (*(bool*)values.back()) {
			if (callfunctions(values, errorcodepointer, forced, stream)) {
				return;
			}
		}
	}
}