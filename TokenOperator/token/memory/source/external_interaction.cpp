#include "../include/external_interaction.h"
namespace memory {
	namespace external {
		void importdllstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if ((*argumentspointer)[0] && (*argumentspointer)[1]) {
				*(void**)(*argumentspointer)[1] = LoadLibrary((LPCWSTR)(*argumentspointer)[0]);
			}
			else {
				if (errorcodepointer) {
					*errorcodepointer = 9;	//errorcode (change): both arguments can`t be nullptr
				}
			}
		}
		void getprocaddressstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if ((*argumentspointer)[0] && (*argumentspointer)[1] && (*argumentspointer)[2]) {
				*(void**)(*argumentspointer)[1] = GetProcAddress(*(HMODULE*)(*argumentspointer)[0], (LPCSTR)(*argumentspointer)[2]);	//change "getfunctions" to real function
			}
			else {
				if (errorcodepointer) {
					*errorcodepointer = 8;	//errorcode (change): arguments can`t be nullptr
				}
			}
		}
		void addfunctionsstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			std::vector<basicfunction*>* functions = ((F_LOADER)(*argumentspointer)[0])();
			std::copy(functions->begin(), functions->end(), std::back_inserter(*(std::vector<basicfunction*>*)(*argumentspointer)[1]));
		}
	}
}