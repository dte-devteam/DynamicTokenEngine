#pragma once
//transfer to DynamicTokenEngine project
#include "function.h"
#include "object.h"
#include "metatable.h"
#include "token_data.h"
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


		//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
		//need call initbasefuncion.execute(nullptr, nullptr, false) at start
		static initbasefuncionstruct initbasefuncion {
			token_data::token_name_to_id(L"initbasefuncion"),	//name
			{	//default values
				(void*)&function::importfunction,
				(void*)&function::createfunction,
				(void*)&function::functionloader
			}
		};
		static initmemorystruct initmemory {
			token_data::token_name_to_id(L"initmemory"),	//name
			{	//default values

			}
		};
		static initenginestruct initengine {
			token_data::token_name_to_id(L"initengine"),	//name
			{	//default values
				(void*)sizeof(void*),	//we MUST to create pointers
				(void*)50				//we MUST to create enough pointers for all essential functions
			}
		};
	}
}