#pragma once
#include "../../target_architecture.h"
#include <libloaderapi.h>
#include "../../function/include/functionfactory.h"
namespace memory {
	namespace external {
		struct importdllstructure : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct getprocaddressstructure : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
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