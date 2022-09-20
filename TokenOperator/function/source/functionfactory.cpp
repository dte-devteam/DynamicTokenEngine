#include "../include/functionfactory.h"
namespace functionfactory {
	int test() {
		return 100;
	}
	std::vector<void*> basicfunction::filldefaultvalues(std::vector<void*>* argumentspointer) {
		std::vector<void*> values(defaultvalues);
		if (values.empty() || !argumentspointer) {
			return values;
		}
		size_t i = 0;
		size_t s = values.size();
		for (void* arg : *argumentspointer) {
			values[i] = arg;
			i++;
			if (!(i < s)) break;
		}
		return values;
	}
	void function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		std::vector<void*> values = filldefaultvalues(argumentspointer);
		for (functioncaller func : callings) {
			std::vector<void*> args;
			for (size_t i : func.args_indices) {
				args.push_back(values[i]);
			}
			func.functionpointer->execute(&args, errorcodepointer);
			if (errorcodepointer) {
				if (*errorcodepointer) {
					break;
				}
			}
		}
	}
	void typedfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		std::vector<void*> values;
		std::vector<void*> types;
		if (errorcodepointer) {
			if (argssize < size) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must be given
			}
			else if (argssize < size * 2) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must have type
			}
			values = filldefaultvalues(argumentspointer);
			types = std::vector(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
			if (checktypecompability(&types)) {
				if (errorcodepointer) {
					*errorcodepointer = 0;//errorcode, change
				}
				else {
					//add error log: error: wrong arg types given
				}
			}
		}
		else {
			values = filldefaultvalues(argumentspointer);
			types = std::vector(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
		}
		for (functioncaller func : callings) {
			std::vector<void*> args;
			for (size_t i : func.args_indices) {
				args.push_back(values[i]);
			}
			for (size_t i : func.args_indices) {
				args.push_back(types[i]);
			}
			func.functionpointer->execute(&args, errorcodepointer);
			if (errorcodepointer) {
				if (*errorcodepointer) {
					break;
				}
			}
		}
	}
	void muxfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		std::vector<void*> values;
		std::vector<void*> types;
		if (errorcodepointer) {
			if (argssize < size) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must be given
			}
			else if (argssize < size * 2) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must have type
			}
			values = filldefaultvalues(argumentspointer);
			types = std::vector(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
			if (checktypecompability(&types)) {
				if (errorcodepointer) {
					*errorcodepointer = 0;//errorcode, change
				}
				else {
					//add error log: error: wrong arg types given
				}
			}
		}
		else {
			values = filldefaultvalues(argumentspointer);
			types = std::vector(argumentspointer->begin() + size, argumentspointer->begin() + size * 2);
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
			callings[index].functionpointer->execute(&args, errorcodepointer);
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