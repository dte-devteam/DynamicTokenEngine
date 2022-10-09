#include "../include/pointer.h"
namespace functions {
	namespace pointer {
		void point::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[1]) {
				if (!errorcodepointer || forced) {
					
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
		void unpoint::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values = filldefaultvalues(argumentspointer);
			if (values[1]) {
				if (!errorcodepointer || forced) {
					
				}
			}
			else if (errorcodepointer) {
				*errorcodepointer = 2; //change errorcode: error: can`t operate nullptr
			}
		}
	}
}