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


		//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
		//instances
		static importdllstructure importdll {
			0,	//name
			{	//defaultvalues
				nullptr,	//LPCWSTR of dllname
				nullptr		//where dll pointer should be written
			}
		};
		static getprocaddressstructure getprocaddress {
			0,	//name
			{	//defaultvalues
				nullptr,	//dll entry pointer
				nullptr,	//where proc pointer should be written
				nullptr		//LPCSTR of proc name
			}
		};
	}
}