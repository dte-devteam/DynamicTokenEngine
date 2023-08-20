#include "../include/core_module.h"
#include "../include/root_scope.h"
#include "token/data/include/smart_pointer.h"
#include <iostream>
using namespace dte_core;
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::stream;
using namespace tokenoperator::dte_module;
void add_module_object_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope						(relative root)				NULL - root_scope will be used
	//[1] - module_source				(object metadata)			can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(2)
	std::pair<smart_pointer<object>, bool> target_object = **(module_source*)argument_pointer->get_data()[1];
	scope_path* target_path = ((module_source*)argument_pointer->get_data()[1])->get_path_to_set();
	scope* root = argument_pointer->get_data()[0] ? (scope*)argument_pointer->get_data()[0] : root_scope;
	if (target_path->get_size()) {
		scope* target_root = (scope*)root->get_object(*target_path).get_pointer();
		if (target_root) {
			root = target_root;
		}
		else {
			//to do, create scopes
		}
	}
	if ((*root)[target_object.first->getID()].first) {
		if (!forced) {
			RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
		}
		root->remove_object(target_object.first->getID());
	}
	root->add_object(target_object.first, target_object.second);
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
		nullptr,	//nullptr - to set root scope (see add_object_struct args)
		nullptr
	};
	bf_args args(ARRAYSIZE(objs), objs);
	while (i) {
		args.get_data()[1] = &(*mi)->first[--i];
		((basic_function*)(*core_module_sources[0]).first.get_pointer())->execute(caller, &args, forced);
	}
	EXIT_STACK
}
void execute_function_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope			(relative root)				NULL - root_scope will be used
	//[1] - scope_path		(destination, where to add)	NULL - scope will be taken as function (DO NOT ALLOW [0] & [1] = NULL - this will cause scope execution!)
	//[2] - stream			(caller)					can`t be NULL
	//[3] - bf_args			(function arguments)		can be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(4)
	if (!argument_pointer->get_data()[2]) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	object* root = argument_pointer->get_data()[0] ? argument_pointer->get_data()[0] : root_scope;
	basic_function* function = (basic_function*)(argument_pointer->get_data()[1] ? ((scope*)root)->get_object(*(scope_path*)argument_pointer->get_data()[1]).get_pointer() : root);
	function->execute((stream*)argument_pointer->get_data()[2], (bf_args*)argument_pointer->get_data()[3], forced);
	EXIT_STACK
	//to do, execute
}
void test_core_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	ENTER_STACK
	std::cout << "core imported into root successfully" << std::endl;
	EXIT_STACK
}