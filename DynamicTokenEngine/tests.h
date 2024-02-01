#pragma once
#include <iostream>
#include "token/include/object.h"
#include "token/include/function.h"

#include "module/include/module_instance.h"

#include "utils/include/exec_time.h"

#include "utils/include/debug_defines.h"

#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>

/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)


using namespace dte_token;
using namespace dte_module;
using namespace dte_utils;
inline void test() {
	exec_time et;
	object* o1 = new object{ 1, nullptr, nullptr, {nullptr, 0, 5}, {nullptr, 0, 5} };
	object* o2 = new object{ 2, nullptr, nullptr, {nullptr, 0, 5}, {nullptr, 0, 5} };
	object* o3 = new object{ 3, nullptr, nullptr, {nullptr, 0, 5}, {nullptr, 0, 5} };
	object* o4 = new object{ 4, nullptr, nullptr, {nullptr, 0, 5}, {nullptr, 0, 5} };
	o1->add_object(o1);
	o1->add_object(o2);
	o1->add_object(o3);
	o1->add_object(o4);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (size_t i = o1->b.us; i;) {
			std::cout << o1->b.a[--i] << std::endl;
		}
	)
	o1->remove_object(o2);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (size_t i = o1->b.us; i;) {
			std::cout << o1->b.a[--i] << std::endl;
		}
		float fff = 0;
		std::cout << STR_DECL_TYPE(fff) << std::endl;
	)

	object_handler ops[] = {
		{o1, 1}, {o3, 2}, {o4, 3}
	};
	stream_data sd;
	args _args(ops);
	_fp(sd, _args);


	std::cout << (*o1->b.find([ID = 3](object*& o) { return o->ID == ID; }))->ID << std::endl;


	dynamic_array<object_handler> da1(ops, 3, 7);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object_handler& oh : da1) {
			std::cout << oh.ID << std::endl;
		}
	)
	dynamic_array<object_handler> da2(da1, 1, 2, 8);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object_handler& oh : da2) {
			std::cout << oh.ID << std::endl;
		}
	)
	std::cout << "dt: " << et.get_dt() << "ms" << std::endl;
}