#pragma once
#pragma warning(disable:4275) //solve this later!
#include "function/include/functionfactory.h"
using namespace functionfactory;
namespace functions {
	namespace algebra {
		namespace sub {
			//constructors
			//(-)
			struct int_sub_function : basicfunction {
				using basicfunction::basicfunction;
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
			};
			struct float_sub_function : basicfunction {
				using basicfunction::basicfunction;
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
			};
			//instances
			//(-)
			inline int_sub_function int_sub{
				0,
				{
					nullptr,
					nullptr,
					nullptr
				}
			};
			inline float_sub_function float_sub{
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