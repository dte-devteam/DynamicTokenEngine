#include "../include/triggeredfunction.h"
namespace function {
	void triggeredfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		//note: values.back() will be read as bool*, so overriding it to noncastable for bool* type will cause crash
		if (check(argumentspointer, errorcodepointer)) {
			std::vector<void*> values;
			filldefaultvalues(argumentspointer, values);
			if (*(bool*)values.back()) {
				callfunctions(values, errorcodepointer, forced, stream);
			}
		}
	}
	bool triggeredfunction::check(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) {
		if (defaultvalues.empty()) {
			if (errorcodepointer) {
				*errorcodepointer = 0;//errorcode, change
			}
			return false;	//init-error: function must know bool value, default values create space for this check
		}
		return true;
	}
}