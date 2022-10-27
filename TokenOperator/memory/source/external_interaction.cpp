#include "../include/external_interaction.h"
using namespace functionfactory;
namespace memory {
	namespace external {
		void importdllstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values;
			filldefaultvalues(argumentspointer, &values);
			HMODULE dllentry = NULL;
			if (values[0] && values[1]) {
				dllentry = LoadLibrary((LPCWSTR)values[0]);
			}
			else {
				if (errorcodepointer) {
					*errorcodepointer = 9;	//errorcode (change): both arguments can`t be nullptr
				}
			}
		}
		void getprocaddressstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values;
			filldefaultvalues(argumentspointer, &values);
			void* vectoroffunctions = nullptr;
			if (values[0] && values[1] && values[2]) {
				vectoroffunctions = (void*)GetProcAddress(*(HMODULE*)values[0], (LPCSTR)values[2]);	//change "getfunctions" to real function
			}
			else {
				if (errorcodepointer) {
					*errorcodepointer = 8;	//errorcode (change): arguments can`t be nullptr
				}
			}
		}
	}
}