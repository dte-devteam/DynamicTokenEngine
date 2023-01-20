#include "../include/errorvalues.h"
namespace functionfactory {
	namespace errorvalues {
		void errorcode::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (errorcodepointer) {
				if (*errorcodepointer < errorvalues.size()) {
					std::wcout << "ERROR CODE: " << errorvalues[*errorcodepointer] << std::endl;
				}
			}
		}
	}
}