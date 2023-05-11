#pragma once
#include "functioncaller.h"
namespace function {
	struct function : basicfunction {
		function(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {});
		std::vector<functioncaller> callings; //make this protected!
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		protected:
			bool callfunctions(std::vector<void*>& values, uint64_t* errorcodepointer, bool forced, void* stream);
	};
}