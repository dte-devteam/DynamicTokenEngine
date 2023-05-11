#pragma once
#include "function.h"
namespace function {
	struct muxfunction : function {
		muxfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, basicfunction* mux = nullptr);
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		basicfunction* mux;
	};
}