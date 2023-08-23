#include "../include/core_module.h"
#include "../include/root_scope.h"
#include "token/data/include/smart_pointer.h"
#include <iostream>
using namespace dte_core;
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::stream;
using namespace tokenoperator::dte_module;
void use_scope_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope			(relative root)				can`t be NULL
	//[1] - scope_path		(path to create)			can`t be NULL
	//[2] - scope*			(scope output, optional)	NULL - result won`t be returned
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(2)
	scope* root = (scope*)argument_pointer->get_data()[0];
	scope_path* path = (scope_path*)argument_pointer->get_data()[1];
	scope** result = argument_pointer->get_size() > 2 ? (scope**)argument_pointer->get_data()[2] : nullptr;
	if (!root) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	if (!path) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	size_t i = 0;
	while (i < path->get_size()) {
		if ((**path)[i].second) {
			//back
			scope_path step(1, **path + i);
			root = (scope*)root->get_object(step).get_pointer();
			if (!root) {
				RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
			}
		}
		else {
			//forward
			smart_pointer<scope> node = new scope(1, 0, (**path)->first);
			if (!root->add_object(node, true)) {
				RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
			}
			root = node;
		}
		++i;
	}
	if (result) {
		*result = root;
	}
	EXIT_STACK
}
void add_module_object_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope			(relative root)				can`t be NULL
	//[1] - module_source	(object metadata)			can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(2)
	scope* root = (scope*)argument_pointer->get_data()[0];
	module_source* ms = (module_source*)argument_pointer->get_data()[1];
	if (!root) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	if (!ms) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	std::pair<smart_pointer<object>, bool> target_object = **ms;
	scope_path* target_path = ms->get_path_to_set();
	object* objs[] = {
		root,
		target_path,
		(object*)&root
	};
	bf_args args(ARRAYSIZE(objs), objs);
	((basic_function*)(*core_module_sources[0]).first.get_pointer())->execute(caller, &args, forced);
	if ((*root)[target_object.first->getID()].first) {
		if (!forced) {
			RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
		}
		root->remove_object(target_object.first->getID());
	}
	root->add_object(target_object.first, target_object.second);
	EXIT_STACK
}
void add_module_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - module_info		(module data for adding)	can`t be NULL
	ENTER_STACK
	REQUIRE_ARGS
	REQUIRE_ARG_NUM(1)
	module_info* mi = (module_info*)argument_pointer->get_data()[0];
	if (!mi) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	size_t i = (*mi)->second;
	uint64_t module_ID = tokenoperator::dte_token::TOKEN_NAME(mi->get_dllname().c_str());
	smart_pointer<object> module_scope = (*root_scope)[module_ID].first;	//if module needs to be overriden - we dont duplicate module scope, we change already existing one
	if (!module_scope.get_pointer()) {
		module_scope = new scope(i, i, module_ID);
	}
	root_scope->add_object(module_scope, true);
	object* objs[] = {
		module_scope,
		nullptr
	};
	bf_args args(ARRAYSIZE(objs), objs);
	while (i) {
		args.get_data()[1] = &(*mi)->first[--i];
		((basic_function*)(*core_module_sources[1]).first.get_pointer())->execute(caller, &args, forced);
	}
	EXIT_STACK
}
void import_module_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - value<std::wstring>		(module name for import)	can`t be NULL
	ENTER_STACK
	smart_pointer<module_info> mi = new module_info(**(value<std::wstring>*)argument_pointer->get_data()[0]);
	object* objs[] = {
		mi
	};
	bf_args args(ARRAYSIZE(objs), objs);
	((basic_function*)(*core_module_sources[2]).first.get_pointer())->execute(caller, &args, forced);
	//to do add to special scope to stroe module data
	EXIT_STACK
}
void execute_function_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	//[0] - scope			(relative root)				NULL - root_scope will be used
	//[1] - scope_path		(destination, where to add)	NULL - scope will be taken as function (DO NOT ALLOW [0] & [1] = NULL - this will cause scope execution!)
	//[2] - stream			(caller)					can`t be NULL
	//[3] - bf_args			(function arguments)		can be NULL
	//to do (should get module data for safe launch)
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
	//to do, wrap in stream and execute
}
void test_core_struct::execute(stream* caller, bf_args* argument_pointer, bool forced) {
	ENTER_STACK
	std::cout << "core imported into root successfully" << std::endl;
	EXIT_STACK
}