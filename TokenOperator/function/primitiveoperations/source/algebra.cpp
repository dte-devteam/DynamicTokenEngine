#include "../include/algebra.h"
namespace functions {
	namespace algebra {
		//(+)
		void int_add_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(int*)values[2] = *(int*)values[0] + *(int*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		void float_add_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(float*)values[2] = *(float*)values[0] + *(float*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		//(-)
		void int_sub_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(int*)values[2] = *(int*)values[0] - *(int*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		void float_sub_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(float*)values[2] = *(float*)values[0] - *(float*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		//(*)
		void int_mul_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(int*)values[2] = *(int*)values[0] * *(int*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		void float_mul_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(float*)values[2] = *(float*)values[0] * *(float*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		//(/)
		void int_div_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (*(int*)values[1] == 0) {
					if (errorcodepointer) {
						*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
					}
					return;
				}
				if (!errorcodepointer || forced) {
					*(int*)values[2] = *(int*)values[0] / *(int*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		void float_div_function::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[2] && values[1] && values[0]) {
				if (!errorcodepointer || forced) {
					*(float*)values[2] = *(float*)values[0] / *(float*)values[1];
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
	}
}