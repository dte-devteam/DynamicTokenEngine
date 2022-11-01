#pragma once
#include "function.h"
#include "object.h"
#include "metatable.h"
namespace memory {
	namespace init {
		struct initbasefuncionstruct : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
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
	}
}