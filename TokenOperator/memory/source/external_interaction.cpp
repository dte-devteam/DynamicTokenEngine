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
					return;
				}
			}
			if (!errorcodepointer || forced) {
				*(HMODULE*)values[1] = dllentry;
			}
			else if (errorcodepointer && !dllentry) {
				*errorcodepointer = 5;	//errorcode (change): failed to load dll entry
			}
		}
		void getprocaddressstructure::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			std::vector<void*> values;
			filldefaultvalues(argumentspointer, &values);
			FARPROC vectoroffunctions = NULL;
			if (values[0] && values[1] && values[2]) {
				vectoroffunctions = GetProcAddress(*(HMODULE*)values[0], (LPCSTR)values[2]);	//change "getfunctions" to real function
			}
			else {
				if (errorcodepointer) {
					*errorcodepointer = 8;	//errorcode (change): arguments can`t be nullptr
					return;
				}
			}
			if (!errorcodepointer || forced) {
				*(FARPROC*)values[1] = vectoroffunctions;
			}
			else if (errorcodepointer && !vectoroffunctions) {
				*errorcodepointer = 2;	//errorcode (change): failed to load dll function list
			}
		}
	}
}