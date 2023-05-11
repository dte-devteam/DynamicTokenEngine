#include "../include/function.h"
namespace function {
	function::function(uint64_t id, std::vector<void*> defaultvalues, std::vector<functioncaller> callings) : basicfunction(id, defaultvalues), callings(callings) {}
	void function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		callfunctions(values, errorcodepointer, forced, stream);
	}
	bool function::callfunctions(std::vector<void*>& values, uint64_t* errorcodepointer, bool forced, void* stream) {
		for (functioncaller& func : callings) {
			std::vector<void*> args;
			for (std::pair<size_t, bool>& i : func.args_indices) {
				args.push_back(i.second ? (void*)i.first : values[i.first]);
			}
			func.functionpointer->execute(&args, errorcodepointer, forced, stream);
			if (HAS_E) {
				return true;
			}
		}
		return false;
	}
}