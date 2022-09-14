#pragma once
#include "functionfactory.h"
using namespace functionfactory;
namespace functions {
	namespace algebra {
		struct int_add : basicfunction {
			bool execute(std::vector<void*>* argumentspointer, bool errorpossible) {
				*(int*)(*argumentspointer)[2] = *(int*)(*argumentspointer)[1] + *(int*)(*argumentspointer)[0];
				return false;
			}
		};
		struct float_add : basicfunction {
			bool execute(std::vector<void*>* argumentspointer, bool errorpossible) {
				*(float*)(*argumentspointer)[2] = *(float*)(*argumentspointer)[1] + *(float*)(*argumentspointer)[0];
				return false;
			}
		};
		struct double_add : basicfunction {
			bool execute(std::vector<void*>* argumentspointer, bool errorpossible) {
				*(double*)(*argumentspointer)[2] = *(double*)(*argumentspointer)[1] + *(double*)(*argumentspointer)[0];
				return false;
			}
		};
		struct int_addadd : function {};//temp
		struct add : muxfunction {
			size_t mux(std::vector<void*>* valuespointer, std::vector<void*>* typespointer) {
				if ((*typespointer)[0] == (*typespointer)[1] && (*typespointer)[0] == (*typespointer)[2]) {
					//to do
					return 0;//temp
				}
				else {
					return callings.size();
				}
			}
		};
		//static int_add add;
	}
}