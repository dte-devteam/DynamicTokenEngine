#pragma once
#include "function.h"
namespace function {
	struct cyclefunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
}