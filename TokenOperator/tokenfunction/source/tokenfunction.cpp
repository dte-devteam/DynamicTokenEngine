#include "../include/tokenfunction.h"
namespace tokenfunction {
	std::vector<argument> basicfunction::filldefaultvalues(std::vector<argument> args) {
		std::vector<argument> values(defaultvalues);
		for (argument arg : args) {
			std::vector<argument>::iterator iterator = std::find_if(values.begin(), values.end(), [arg](argument value) { return value.name == arg.fieldtarget; });
			if (iterator != args.end()) {
				size_t index = std::distance(values.begin(), iterator);
				if (std::find(types[index].begin(), types[index].end(), arg.type) == types[index].end()) {
					//error, cannot fill
				}
				else {
					iterator->valuepointer = arg.valuepointer;
					iterator->type = arg.type;
				}
			}
		}
		return values;
	}
	void function::execute(std::vector<argument> args) {
		std::vector<argument> values = filldefaultvalues(args);
		std::vector<argument> subfunctionvalues;
		for (functioncaller function : subfunctions) {
			subfunctionvalues.clear();
			for (uint64_t name_iter : function.args_name) {
				for (argument arg_iter : args) {
					if (name_iter == arg_iter.name) {
						subfunctionvalues.push_back(arg_iter);
						break;
					}
				}
			}
			if (function.functionpointer) {
				function.functionpointer->execute(subfunctionvalues);
			}
			else {
				//add log
			}
		}
	}
}