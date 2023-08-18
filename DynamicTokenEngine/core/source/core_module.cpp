#include "../include/core_module.h"
#include "../include/root_scope.h"
#include "token/data/include/smart_pointer.h"
#include <iostream>
using namespace dte_core;
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::stream;
using namespace tokenoperator::dte_module;
void add_object_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope						(relative root)				NULL - root_scope will be used)
	//[1] - scope_path					(destination, where to add)	can`t be NULL
	//[2] - smart_pointer<object>		(source)					can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(3)
	std::cout << "hi" << std::endl;
	EXIT_STACK
	//to do, add any object to any scope
	//if forced - replace
}
void add_module_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - module_info					(module data for import)	can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(1)
	module_info* mi = (module_info*)argument_pointer->get_data()[0];
	if (!mi) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	size_t i = (*mi)->second;
	object* objs[] = {
		nullptr,
		nullptr,
		nullptr
	};
	bf_args args(ARRAYSIZE(objs), objs);
	while (i) {
		args.get_data()[1] = (*mi)->first[--i].get_path_to_set();
		args.get_data()[2] = (*mi)->first[i].get_pointer();
		((basic_function*)(*core_module_sources[0]).get_pointer())->execute(caller, &args, forced);
	}
	EXIT_STACK
	//to do, add all objects to root scope
}
void execute_function_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope			(relative root)				NULL - root_scope will be used)
	//[1] - scope_path		(destination, where to add)	can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(2)
	EXIT_STACK
	//to do, execute
}