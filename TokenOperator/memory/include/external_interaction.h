#pragma once
#include "target_architecture.h"
#include <libloaderapi.h>
#include "function/include/functionfactory.h"
namespace memory {
	namespace external {
		typedef std::vector<functionfactory::basicfunction*>* (*F_LOADER)();
		//constructors
		struct importdllstructure : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct getprocaddressstructure : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct addfunctionsstructure : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
	}
}