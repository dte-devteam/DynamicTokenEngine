#pragma once
#include "../../target_architecture.h"
#include <libloaderapi.h>
#include "../../function/include/functionfactory.h"
using namespace std;
using namespace functionfactory;
namespace memory {
	namespace external {
		struct importdllstructure : basicfunction {
			using basicfunction::basicfunction;
			void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct getprocaddressstructure : basicfunction {
			using basicfunction::basicfunction;
			void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
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