#include "../include/typedfunction.h"
namespace function {
	typedfunction::typedfunction(uint64_t id, std::vector<void*> defaultvalues, std::vector<functioncaller> callings, std::vector<std::vector<void*>> valuetypes) : function(id, defaultvalues, callings), valuetypes(valuetypes) {}
	void typedfunction::filltypes(std::vector<void*>::iterator start, std::vector<void*>::iterator end, std::vector<void*>* target) {
		std::vector<void*> types(start, end);
		*target = types;
	}
	void typedfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		std::vector<void*> values;
		std::vector<void*> types;
		if (errorcodepointer) {
			if (argssize < size * 2) {
				*errorcodepointer = 21;//errorcode, change
				return;	//error: all values must have type
			}
			else if (argssize < size) {
				*errorcodepointer = 20;//errorcode, change
				return;	//error: all values must be given
			}
			filldefaultvalues(argumentspointer, values);
			filltypes(argumentspointer->begin() + size, argumentspointer->end(), &types);
			if (checktypecompability(&types)) {
				if (errorcodepointer) {
					*errorcodepointer = 22; //errorcode, change
				}
				else {
					//add error log: error: wrong arg types given
				}
				return;
			}
		}
		else {
			filldefaultvalues(argumentspointer, values);
			filltypes(argumentspointer->begin() + size, argumentspointer->end(), &types);
		}
		for (functioncaller& func : callings) {
			std::vector<void*> args;
			for (std::pair<size_t, bool>& p : func.args_indices) {
				if (p.second) {
					args.push_back((void*)p.first);
				}
				else {
					args.push_back(values[p.first]);
				}
			}
			for (std::pair<size_t, bool>& p : func.args_indices) {
				if (p.second) {
					args.push_back((void*)p.first);
				}
				else {
					args.push_back(types[p.first]);
				}
			}
			func.functionpointer->execute(&args, errorcodepointer, forced, stream);
			if (HAS_E) {
				break;
			}
		}
	}
	bool typedfunction::checktypecompability(std::vector<void*>* types) {
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