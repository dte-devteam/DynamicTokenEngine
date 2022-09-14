#include "../include/functionfactory.h"
namespace functionfactory {
	int test() {
		return 100;
	}
	std::vector<void*> basicfunction::filldefaultvalues(std::vector<void*>* argumentspointer) {
		std::vector<void*> values(defaultvalues);
		if (values.empty()) return values;
		size_t i = 0;
		size_t s = values.size();
		for (void* arg : *argumentspointer) {
			values[i] = arg;
			i++;
			if (!(i < s)) break;
		}
		return values;
	}
	bool function::execute(std::vector<void*>* argumentspointer, bool errorpossible) {
		if (errorpossible) {
			return true;	//error handler: crash preventing
		}
		std::vector<void*> values = filldefaultvalues(argumentspointer);
		for (functioncaller func : callings) {
			std::vector<void*> args;
			for (size_t i : func.args_indices) {
				args.push_back(values[i]);
			}
			func.functionpointer->execute(&args, false);
		}
		return false;
	}
	bool typedfunction::execute(std::vector<void*>* argumentspointer, bool errorpossible) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		if (argssize < size) {
			return true;	//error: all values must be given
		}
		else if (argssize < size * 2) {
			return true;	//error: all values must have type
		}
		std::vector<void*> values = filldefaultvalues(argumentspointer);
		std::vector<void*> types(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
		if (errorpossible) {
			if (checktypecompability(&types)) {
				return true;	//error: wrong arg types given
			}
		}
		for (functioncaller func : callings) {
			std::vector<void*> args;
			for (size_t i : func.args_indices) {
				args.push_back(values[i]);
			}
			for (size_t i : func.args_indices) {
				args.push_back(types[i]);
			}
			if (func.functionpointer->execute(&args, false)) {
				return true;	//error: subfunction error
			}
		}
		return false;
	}
	bool muxfunction::execute(std::vector<void*>* argumentspointer, bool errorpossible) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		if (argssize < size) {
			return true;	//error: all values must be given
		}
		else if (argssize < size * 2) {
			return true;	//error: all values must have type
		}
		std::vector<void*> values = filldefaultvalues(argumentspointer);
		std::vector<void*> types(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
		if (errorpossible) {
			if (checktypecompability(&types)) {
				return true;	//error: wrong arg types given
			}
		}
		size_t index = mux(&values, &types);
		if (index < callings.size()) {
			std::vector<void*> args;
			for (size_t i : callings[index].args_indices) {
				args.push_back(values[i]);
			}
			for (size_t i : callings[index].args_indices) {
				args.push_back(types[i]);
			}
			return callings[index].functionpointer->execute(&args, false);	//if true: error: subfunction error
		}
		else {
			return true;	//error: can`t find case for execution 
		}
	}
	bool typedfunction::checktypecompability(std::vector<void*>* argumentspointer) {
		if (argumentspointer->empty()) return false;
		size_t i = 0;
		for (void* arg : *argumentspointer) {
			if (std::find_if(valuetypes[i].begin(), valuetypes[i].end(), [arg](void* value) { return value == arg; }) == valuetypes[i].end()) {
				return true;
			}
			i++;
		}
		return false;
	}
}