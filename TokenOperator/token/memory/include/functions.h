#pragma once
#include "token/function/include/basicfunction.h"
#include "token/function/include/typedfunction.h"
#include "token/function/include/muxfunction.h"
namespace memory {
	struct importfunctionstruct : function::typedfunction {
		using typedfunction::typedfunction;
	};
	struct createfunctionstruct : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
	};
	struct functionloaderstruct : function::muxfunction {
		using muxfunction::muxfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
	};
}