#include "../include/functionfactory.h"
#include "../../memory/include/stream.h"
namespace functionfactory {
	int r() {
		return 100;
	}
	basicfunction::basicfunction(uint64_t id, std::vector<void*> defaultvalues) : id(id), defaultvalues(defaultvalues) {}
	function::function(uint64_t name, std::vector<void*> defaultvalues, std::vector<functioncaller> callings) : basicfunction(name, defaultvalues), callings(callings) {}
	typedfunction::typedfunction(uint64_t name, std::vector<void*> defaultvalues, std::vector<functioncaller> callings, std::vector<std::vector<void*>> valuetypes) : function(name, defaultvalues, callings), valuetypes(valuetypes) {}
	muxfunction::muxfunction(uint64_t name, std::vector<void*> defaultvalues, std::vector<functioncaller> callings, basicfunction* mux) : function(name, defaultvalues, callings), mux(mux){}
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
	void typedfunction::filltypes(std::vector<void*>::iterator start, std::vector<void*>::iterator end, std::vector<void*>* target) {
		std::vector<void*> types(start, end);
		*target = types;
	}
	bool function::callfunctions(std::vector<void*>* values, uint64_t* errorcodepointer, bool forced, void* stream) {
		for (functioncaller& func : callings) {
			std::vector<void*> args;
			for (std::pair<size_t, bool>& i : func.args_indices) {
				args.push_back(i.second ? (void*)i.first : (*values)[i.first]);
			}
			func.functionpointer->execute(&args, errorcodepointer, forced, stream);
			if (HAS_E) {
				return true;
			}
		}
		return false;
	}
	void function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		callfunctions(&values, errorcodepointer, forced, stream);
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
	void muxfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		size_t index = callings.size();
		std::vector<void*> mux_args{ &index };
		std::copy(argumentspointer->begin() + values.size() - 1, argumentspointer->end(), std::back_inserter(mux_args));
		mux->execute(&mux_args, errorcodepointer, forced, stream);
		if (HAS_E) {
			return;
		}
		if (index < callings.size()) {
			std::vector<void*> args;
			for (std::pair<size_t, bool>& p : callings[index].args_indices) {
				if (p.second) {
					args.push_back((void*)p.first);
				}
				else {
					args.push_back(values[p.first]);
				}
			}
			callings[index].functionpointer->execute(&args, errorcodepointer, forced, stream);
		}
	}
	void unreliablefunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		if (errorcodepointer) {
			if (*errorcodepointer == 1) {
				callfunctions(&values, errorcodepointer, true, stream);
			}
			else if (*errorcodepointer == 0) {
				//to do
				//clone data
				*errorcodepointer = 1;
				callfunctions(&values, errorcodepointer, true, stream);
				//to do
				//write from clone to data
			}
		}
		else {
			callfunctions(&values, errorcodepointer, forced, stream);
		}
	}
	void triggeredfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		//note: values.back() will be read as bool*, so overriding it to noncastable for bool* type will cause crash
		if (check(argumentspointer, errorcodepointer)) {
			std::vector<void*> values;
			filldefaultvalues(argumentspointer, values);
			if (*(bool*)values.back()) {
				callfunctions(&values, errorcodepointer, forced, stream);
			}
		}
	}
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
			if (callfunctions(&values, errorcodepointer, forced, stream)) {
				return;
			}
		}
	}
	bool typedfunction::checktypecompability(std::vector<void*>* types) {
		for (size_t i = 0; i < valuetypes.size(); i++) {
			for (void*& arg : *types) {
				if (find_if(valuetypes[i].begin(), valuetypes[i].end(), [arg](void* value) { return value == arg; }) == valuetypes[i].end()) {
					return true;
				}
			}
		}
		return false;
	}
	bool subtypedfunction::checktypecompability(std::vector<void*>* types) {
		for (size_t i = 0; i < types->size(); i++) {
			(*types)[i] = (void*)((size_t)(*types)[i] >> 32);
		}
		for (size_t i = 0; i < valuetypes.size(); i++) {
			for (void*& arg : *types) {
				if (find_if(valuetypes[i].begin(), valuetypes[i].end(), [arg](void* value) { return value == arg; }) == valuetypes[i].end()) {
					return true;
				}
			}
		}
		return false;
	}
	bool triggeredfunction::check(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		if (defaultvalues.empty()) {
			if (errorcodepointer) {
				*errorcodepointer = 0;//errorcode, change
			}
			return false;	//init-error: function must know bool value, default values create space for this check
		}
		return true;
	}
}