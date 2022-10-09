#pragma once
#include "function.h"
#include "modulecollector.h"
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
				(void*)new functions::algebra::int_add_function(
					0,	//name (change)
					{	//default values
						nullptr,	//A
						nullptr,	//B
						nullptr		//R (R=A+B <int>)
					}
				)
			}
		};
	}
}