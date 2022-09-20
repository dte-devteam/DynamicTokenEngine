#pragma once
#include "functionfactory.h"
using namespace functionfactory;
namespace functions {
	namespace algebra {
		struct int_add_function : basicfunction {
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
				std::vector<void*> values = filldefaultvalues(argumentspointer);
				*(int*)values[2] = *(int*)values[1] + *(int*)values[0];
			}
		};
		struct float_add_function : basicfunction {
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
				std::vector<void*> values = filldefaultvalues(argumentspointer);
				*(float*)values[2] = *(float*)values[1] + *(float*)values[0];
			}
		};
		struct double_add_function : basicfunction {
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
				std::vector<void*> values = filldefaultvalues(argumentspointer);
				*(double*)values[2] = *(double*)values[1] + *(double*)values[0];
			}
		};
		struct int_addadd : function {};//temp
		struct add_funtion : muxfunction {
			size_t mux(std::vector<void*>* valuespointer, std::vector<void*>* typespointer) {
				if ((*typespointer)[0] == (*typespointer)[1] && (*typespointer)[0] == (*typespointer)[2]) {
					if ((*typespointer)[0] == (void*)0) {
						return 0;
					}
					else if ((*typespointer)[0] == (void*)1) {
						return 1;
					}
					else if ((*typespointer)[0] == (void*)2) {
						return 2;
					}
				}
				else {
					return callings.size();
				}
			}
		};
		static int_add_function int_add;
		static float_add_function float_add;
		static double_add_function double_add;
		static add_funtion add;
		inline void init() {
			int_add.name = 1;
			int_add.defaultvalues = {
				nullptr,
				nullptr,
				nullptr
			};
			float_add.name = 2;
			float_add.defaultvalues = {
				nullptr,
				nullptr,
				nullptr
			};
			double_add.name = 3;
			double_add.defaultvalues = {
				nullptr,
				nullptr,
				nullptr
			};


			add.name = 2;
			add.defaultvalues = {
				nullptr,
				nullptr,
				nullptr
			};
			add.valuetypes = {
				{
					(void*)0,
					(void*)1,
					(void*)2
				},
				{
					(void*)0,
					(void*)1,
					(void*)2
				},
				{
					(void*)0,
					(void*)1,
					(void*)2
				},
			};
			add.callings = {
				{
					&int_add,
					{
						0,
						1,
						2
					}
				},
				{
					&float_add,
					{
						0,
						1,
						2
					}
				},
				{
					&double_add,
					{
						0,
						1,
						2
					}
				}
			};
		}
	}
}