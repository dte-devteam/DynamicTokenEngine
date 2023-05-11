#pragma once
#include "target_architecture.h"
#include <libloaderapi.h>
#include "token/function/include/basicfunction.h"
namespace memory {
	namespace external {
		typedef std::vector<function::basicfunction*>* (*F_LOADER)();
		//constructors
		struct importdllstructure : function::basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct getprocaddressstructure : function::basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct addfunctionsstructure : function::basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
	}
}