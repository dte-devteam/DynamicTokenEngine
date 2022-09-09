#include "../include/tokenfunction.h"

std::vector<tokenfunction::argument> tokenfunction::basicfunction::filldefaultvalues(std::vector<tokenfunction::argument> args) {
	std::vector<argument> values(defaultvalues);
	for (argument value : values) {
		std::vector<argument>::iterator iterator = std::find_if(args.begin(), args.end(), [value](argument arg) { return value.name == arg.name; });
		if (iterator != args.end()) {
			value.valuepointer = iterator->valuepointer;
		}
	}
	return values;
}
void tokenfunction::function::execute(std::vector<tokenfunction::argument> args) {
	std::vector<argument> values = filldefaultvalues(args);
	std::vector<argument> subfunctionvalues;
	for (argument value : values) {
		value.name = value.fieldtarget;
		value.fieldtarget = 0;
	}
	for (functioncaller function : subfunctions) {
		subfunctionvalues.clear();
		for (uint64_t arg : function.args_name) {
			std::vector<argument>::iterator end = args.end();
			for (std::vector<argument>::iterator iterator = args.begin(); iterator != end; ++iterator) {
				if (iterator->name == name) subfunctionvalues.push_back(*iterator);
			}
		}
		function.functionpointer->execute(subfunctionvalues);
	}
}