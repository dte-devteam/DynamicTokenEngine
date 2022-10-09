#pragma once
#include "../../include/functionfactory.h"
#include <iostream>
using namespace functionfactory;
namespace functions {
	namespace algebra {
		//constructors
		//(+)
		struct int_add_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct float_add_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		//(-)
		struct int_sub_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct float_sub_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		//(*)
		struct int_mul_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct float_mul_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		//(/)
		struct int_div_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct float_div_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		//(%)
		//instances
		//(+)
		static int_add_function int_add {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		static float_add_function float_add {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(-)
		static int_sub_function int_sub {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		static float_sub_function float_sub {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(*)
		static int_mul_function int_mul {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		static float_mul_function float_mul {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(/)
		static int_div_function int_div {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		static float_div_function float_div {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(%)
	}
}