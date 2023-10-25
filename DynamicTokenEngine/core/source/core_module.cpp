#include "../include/core_module.h"
#include "../include/root_scope.h"
#include "token/data/include/smart_pointer.h"
#include <iostream>
using namespace dte_core;
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::stream;
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_module;
void use_scope_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	//[0] - scope			(relative root)				NULL - root scope will be used
	//[1] - scope_path		(path to create)			can`t be NULL
	//[2] - scope*			(scope output, optional)	NULL - result won`t be returned
	ENTER_STACK
	REQUIRE_ARG_NUM(2)
	scope* root = (scope*)((bf_args&)args)[0];
	if (!root) {
		root = root_scope;
	}
	scope_path* path = (scope_path*)args.get_data()[1];
	scope** result = args.get_size() > 2 ? (scope**)args.get_data()[2] : nullptr;
	if (!path) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	size_t i = 0;
	while (i < path->get_size()) {
		if (path->get_value()[i].second) {
			//back
			scope_path step(1, path->get_value() + i);
			root = (scope*)root->get_object(step).get_pointer();
			if (!root) {
				RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
			}
		}
		else {
			//forward
			smart_pointer<scope> node = new scope(1, 0, path->get_value()[i].first);
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
void add_module_object_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	//[0] - scope			(relative root)				can`t be NULL
	//[1] - module_source	(object metadata)			can`t be NULL
	ENTER_STACK
	REQUIRE_ARG_NUM(2)
	scope* root = (scope*)args.get_data()[0];
	module_source* ms = (module_source*)args.get_data()[1];
	if (!root) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	if (!ms) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR);
	}
	std::pair<smart_pointer<object>, bool> target_object = ms->get_value();
	scope_path* target_path = ms->get_path_to_set();
	object* objs[] = {
		root,
		target_path,
		(object*)&root
	};
	bf_args use_scope_args(ARRAYSIZE(objs), objs);
	((basic_function*)core_module_sources[0].get_value().first.get_pointer())->execute(caller, use_scope_args, forced);
	if ((*root)[target_object.first->getID()].first) {
		if (!forced) {
			RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
		}
		root->remove_object(target_object.first->getID());
	}
	root->add_object(target_object.first, target_object.second);
	EXIT_STACK
}
void add_module_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	//[0] - module_info		(module data for adding)	can`t be NULL
	ENTER_STACK
	REQUIRE_ARG_NUM(1)
	module_info* mi = (module_info*)args.get_data()[0];
	if (!mi) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	size_t i = mi->get_value().second;
	uint64_t module_ID = TOKEN_NAME(mi->get_dllname().c_str());
	smart_pointer<object> module_scope = (*root_scope)[module_ID].first;	//if module needs to be overriden - we dont duplicate module scope, we change already existing one
	if (!module_scope.get_pointer()) {
		module_scope = new scope(i, i, module_ID);
	}
	root_scope->add_object(module_scope, true);
	object* objs[] = {
		module_scope,
		nullptr
	};
	bf_args obj_adder_args(ARRAYSIZE(objs), objs);
	while (i) {
		obj_adder_args.get_data()[1] = &mi->get_value().first[--i];
		((basic_function*)core_module_sources[1].get_value().first.get_pointer())->execute(caller, obj_adder_args, forced);
	}
	EXIT_STACK
}
void import_module_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	//[0] - value<std::wstring>		(module name for import)	can`t be NULL
	ENTER_STACK
	REQUIRE_ARG_NUM(1)
	value<std::wstring>* module_name = (value<std::wstring>*)args.get_data()[0];
	smart_pointer<module_info> mi = new module_info(module_name->get_value(), TOKEN_NAME(module_name->get_value().c_str()));
	/*
	* if module already imported - we can`t duplicate (collision will happen)
	* module is defined by name hash
	* for reimporting - unload, than load module
	*/
	//std::wcout << module_name->get_value() << std::endl;//for debug
	//std::wcout << mi->get_value().second << std::endl;//for debug
	//std::cout << mi->get_value().first[0].get_value().first.get_type().get_name() << std::endl;//for debug
	if (((scope*)core_module_sources[6].get_value().first.get_pointer())->add_object(mi)) {
		object* objs[] = {
			mi
		};
		bf_args module_adder_args(ARRAYSIZE(objs), objs);
		((basic_function*)core_module_sources[2].get_value().first.get_pointer())->execute(caller, module_adder_args, forced);
	}
	else {
		RAISE_ERROR(DTE_EC_DATA_COLLISION)
	}
	EXIT_STACK
}
void execute_function_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	//[0] - scope			(root)						NULL - root_scope will be used
	//[1] - scope_path		(final destination)			can`t be NULL
	//[2] - stream			(caller)					can`t be NULL
	//[3] - bf_args			(function arguments)		can be NULL
	//WARNING!
	//This function doesn`t check function init status (because it can be imported, or created)
	ENTER_STACK
	REQUIRE_ARG_NUM(4)
	if (!args.get_data()[1]) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	if (!args.get_data()[2]) {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	object* root = args.get_data()[0] ? args.get_data()[0] : root_scope;
	smart_pointer<object> function = ((scope*)root)->get_object(*(scope_path*)args.get_data()[1]);
	if (!function.get_pointer()) {
		RAISE_ERROR(DTE_EC_DATA_ACCESS_VIOLATION)
	}
	((basic_function*)function.get_pointer())->execute(*(basic_stream*)args.get_data()[2], *(bf_args*)args.get_data()[3], forced);
	EXIT_STACK
}
void test_core_struct::execute(basic_stream& caller, bf_args& args, bool forced) {
	ENTER_STACK
	std::cout << "core imported into root successfully" << std::endl;
	EXIT_STACK
}