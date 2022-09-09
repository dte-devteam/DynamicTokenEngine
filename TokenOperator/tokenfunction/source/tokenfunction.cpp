#include "../include/tokenfunction.h"

std::vector<tokenfunction::argument> tokenfunction::basicfunction::filldefaultvalues(std::vector<tokenfunction::argument> args) {
	std::vector<argument> values(defaultvalues);
	for (argument arg : args) {
		std::vector<argument>::iterator iterator = std::find_if(values.begin(), values.end(), [arg](argument value) { return value.name == arg.fieldtarget; });
		if (iterator != args.end()) {
			iterator->valuepointer = arg.valuepointer;
		}
	}
	return values;
}
void tokenfunction::function::execute(std::vector<tokenfunction::argument> args) {
	std::vector<argument> values = filldefaultvalues(args);
	std::vector<argument> subfunctionvalues;
	std::vector<argument>::iterator arg_iter_begin = args.begin();
	std::vector<argument>::iterator arg_iter_end = args.end();
	std::vector<uint64_t>::iterator name_iter_end;
	for (functioncaller function : subfunctions) {
		subfunctionvalues.clear();
		name_iter_end = function.args_name.end();
		for (uint64_t name_iter : function.args_name) {
			for (std::vector<argument>::iterator arg_iter = arg_iter_begin; arg_iter != arg_iter_end; ++arg_iter) {
				if (name_iter == arg_iter->name) {
					subfunctionvalues.push_back(*arg_iter);
					break;
				}
			}
		}
		function.functionpointer->execute(subfunctionvalues);
	}
}