#pragma once
#pragma warning(disable:4275) //solve this later!
#include "function/include/functionfactory.h"
using namespace functionfactory;
namespace functions {
	namespace algebra {
		namespace div {
			//constructors
			//(/)
			struct int_div_function : basicfunction {
				using basicfunction::basicfunction;
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
			};
			struct float_div_function : basicfunction {
				using basicfunction::basicfunction;
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
			};
			//instances
			//(/)
			inline int_div_function int_div {
				0,
				{
					nullptr,
					nullptr,
					nullptr
				}
			};
			inline float_div_function float_div {
				0,
				{
					nullptr,
					nullptr,
					nullptr
				}
			};
		}
	}
}