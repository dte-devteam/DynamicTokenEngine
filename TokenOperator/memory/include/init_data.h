#pragma once
#include "function.h"
#include "object.h"
#include "metatable.h"
namespace memory {
	namespace init {
		struct initbasefuncionstruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct initmemorystruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct initenginestruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};

		//need call initbasefuncion.execute(nullptr, nullptr, false) at start
		static initbasefuncionstruct initbasefuncion {
			0,	//name (change)
			{	//default values
				(void*)&function::importfunction,
				(void*)&function::createfunction,
				(void*)&function::functionloader
			}
		};
		static initmemorystruct initmemory {
			0,	//name (change)
			{	//default values

			}
		};
		static initenginestruct initengine {
			0,	//name (change)
			{	//default values
				(void*)sizeof(void*),	//we MUST to create pointers
				(void*)50				//we MUST to create enough pointers for all essential functions
			}
		};
	}
}