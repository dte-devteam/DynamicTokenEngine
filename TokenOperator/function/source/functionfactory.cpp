#include "../include/functionfactory.h"
namespace functionfactory {
	int r() {
		return 100;
	}
	basicfunction::basicfunction(uint64_t name, vector<void*> defaultvalues) : name(name), defaultvalues(defaultvalues) {}
	function::function(uint64_t name, vector<void*> defaultvalues, vector<functioncaller> callings) : basicfunction(name, defaultvalues), callings(callings) {}
	typedfunction::typedfunction(uint64_t name, vector<void*> defaultvalues, vector<functioncaller> callings, vector<vector<void*>> valuetypes) : function(name, defaultvalues, callings), valuetypes(valuetypes) {}
	muxfunction::muxfunction(uint64_t name, vector<void*> defaultvalues, vector<functioncaller> callings, vector<vector<void*>> valuetypes, basicfunction* mux) : typedfunction(name, defaultvalues, callings, valuetypes), mux(mux) {}
	void basicfunction::filldefaultvalues(vector<void*>* argumentspointer, vector<void*>* target) {
		vector<void*> values(defaultvalues);
		size_t i = 0;
		size_t s = values.size();
		size_t argsize = argumentspointer->size();
		while (i < s && i < argsize) {
			values[i] = (*argumentspointer)[i];
			i++;
		}
		//values.push_back(argumentspointer);
		*target = values;
	}
	void typedfunction::filltypes(vector<void*>::iterator start, vector<void*>::iterator end, vector<void*>* target) {
		vector<void*> types(start, end);
		*target = types;
	}
	bool function::callfunctions(vector<void*>* values, uint64_t* errorcodepointer, bool forced) {
		size_t values_size = values->size();
		for (functioncaller func : callings) {
			vector<void*> args;
			for (pair<size_t, bool> i : func.args_indices) {
				if (i.second) {
					args.push_back((void*)i.first);
				}
				else {
					args.push_back((*values)[i.first]);
				}
			}
			func.functionpointer->execute(&args, errorcodepointer, forced);
			if (errorcodepointer) {
				if (*errorcodepointer > 1) {
					return true;
				}
			}
		}
		return false;
	}
	void function::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		vector<void*> values;
		filldefaultvalues(argumentspointer, &values);
		callfunctions(&values, errorcodepointer, forced);
	}
	void typedfunction::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		vector<void*> values;
		vector<void*> types;
		if (errorcodepointer) {
			if (argssize < size * 2) {
				*errorcodepointer = 21;//errorcode, change
				return;	//error: all values must have type
			}
			else if (argssize < size) {
				*errorcodepointer = 20;//errorcode, change
				return;	//error: all values must be given
			}
			filldefaultvalues(argumentspointer, &values);
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
			filldefaultvalues(argumentspointer, &values);
			filltypes(argumentspointer->begin() + size, argumentspointer->end(), &types);
		}
		for (functioncaller func : callings) {
			vector<void*> args;
			for (pair<size_t, bool> i : func.args_indices) {
				if (i.second) {
					args.push_back((void*)i.first);
				}
				else {
					args.push_back(values[i.first]);
				}
			}
			for (pair<size_t, bool> i : func.args_indices) {
				if (i.second) {
					args.push_back((void*)i.first);
				}
				else {
					args.push_back(types[i.first]);
				}
			}
			func.functionpointer->execute(&args, errorcodepointer, forced);
			if (errorcodepointer) {
				if (*errorcodepointer > 1) {
					break;
				}
			}
		}
	}
	void muxfunction::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		if (!mux) {
			if (errorcodepointer) {
				*errorcodepointer = 0;//errorcode, change
			}
			return; //init-error: can`t call mux function - function pointer is nullptr
		}
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		vector<void*> values;
		vector<void*> types;
		if (errorcodepointer) {
			if (argssize < size) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must be given
			}
			else if (argssize < size * 2) {
				*errorcodepointer = 0;//errorcode, change
				return;	//error: all values must have type
			}
			filldefaultvalues(argumentspointer, &values);
			filltypes(argumentspointer->begin() + size, argumentspointer->end(), &types);
			if (checktypecompability(&types)) {
				if (errorcodepointer) {
					*errorcodepointer = 0;//errorcode, change
				}
				return; //error: wrong arg types given
			}
		}
		else {
			filldefaultvalues(argumentspointer, &values);
			filltypes(argumentspointer->begin() + size, argumentspointer->end(), &types);
		}
		size_t index = callings.size();
		argumentspointer->push_back(&index);
		if (errorcodepointer) {
			mux->execute(argumentspointer, errorcodepointer, forced);
			if (*errorcodepointer > 1) {
				return;
			}
		}
		mux->execute(argumentspointer, errorcodepointer, forced);
		argumentspointer->pop_back();
		if (index < callings.size()) {
			vector<void*> args;
			for (pair<size_t, bool> i : callings[index].args_indices) {
				if (i.second) {
					args.push_back((void*)i.first);
				}
				else {
					args.push_back(values[i.first]);
				}
			}
			for (pair<size_t, bool> i : callings[index].args_indices) {
				if (i.second) {
					args.push_back((void*)i.first);
				}
				else {
					args.push_back(types[i.first]);
				}
			}
			callings[index].functionpointer->execute(&args, errorcodepointer, forced);
		}
	}
	void unreliablefunction::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		vector<void*> values;
		filldefaultvalues(argumentspointer, &values);
		if (errorcodepointer) {
			if (*errorcodepointer == 1) {
				callfunctions(&values, errorcodepointer, true);
			}
			else if (*errorcodepointer == 0) {
				//to do
				//clone data
				*errorcodepointer = 1;
				callfunctions(&values, errorcodepointer, true);
				//to do
				//write from clone to data
			}
		}
		else {
			callfunctions(&values, errorcodepointer, forced);
		}
	}
	void triggeredfunction::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		//note: values.back() will be read as bool*, so overriding it to noncastable for bool* type will cause crash
		if (check(argumentspointer, errorcodepointer)) {
			vector<void*> values;
			filldefaultvalues(argumentspointer, &values);
			if (*(bool*)values.back()) {
				callfunctions(&values, errorcodepointer, forced);
			}
		}
	}
	void cyclefunction::execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
		//note: pushes back data pointer, new pointer is bool*, so available index++ for callings args
		//advice: for use wrap your functions in construction {function(bool controller, trigger), triggeredfunction{any functions}}, but you can ignore this and use any fucntion combination
		//note: to stop cycle set cycletrigger to false or raise error, cycle will be executing forever if this condition is false
		//advice: for preventing eternal cycles, make threads or raise error in cycle (by iteration number or delta time)
		bool cycletrigger = true;
		vector<void*> values;
		filldefaultvalues(argumentspointer, &values);
		values.push_back(&cycletrigger);
		while (*(bool*)values.back()) {
			if (callfunctions(&values, errorcodepointer, forced)) {
				return;
			}
		}
	}
	bool typedfunction::checktypecompability(vector<void*>* argumentspointer) {
		size_t i = 0;
		for (void* arg : *argumentspointer) {
			if (find_if(valuetypes[i].begin(), valuetypes[i].end(), [arg](void* value) { return value == arg; }) == valuetypes[i].end()) {
				return true;
			}
			i++;
		}
		return false;
	}
	bool triggeredfunction::check(vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		if (defaultvalues.empty()) {
			if (errorcodepointer) {
				*errorcodepointer = 0;//errorcode, change
			}
			return false;	//init-error: function must know bool value, default values create space for this check
		}
		return true;
	}
}