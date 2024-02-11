#pragma once
#include <iostream>
#include "token/include/object.h"
#include "token/include/type.h"
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
		for (object* o : o1->b) {
			std::cout << o << std::endl;
		}
	)
	o1->remove_object(o2);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object* o : o1->b) {
			std::cout << o << std::endl;
		}
		float fff = 0;
		std::cout << STR_DECL_TYPE(fff) << std::endl;
	)

	object_handler ops[] = {
		{o1, 1}, {o3, 2}, {o4, 3}
	};
	stream_data sd;
	_fp(sd, args(ops));

	std::cout << (*o1->b.find([ID = 3](object*& o) { return o->ID == ID; }))->ID << std::endl;

	D_LOG(
		std::cout << "total o1 handlers: " << o1->h << std::endl;
		std::cout << "total o3 handlers: " << o3->h << std::endl;
		std::cout << "total o4 handlers: " << o4->h << std::endl;
	)
	dynamic_array<object_handler> da1(ops, ARRAYSIZE(ops), 0);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object_handler& oh : da1) {
			std::cout << oh.ID << " " << oh->ID << std::endl;
		}
		std::cout << "total o1 handlers: " << o1->h << std::endl;
		std::cout << "total o3 handlers: " << o3->h << std::endl;
		std::cout << "total o4 handlers: " << o4->h << std::endl;
	)
	dynamic_array<object_handler> da2(da1, 0, 2, 0);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object_handler& oh : da2) {
			std::cout << oh.ID << " " << oh->ID << std::endl;
		}
		std::cout << "total o1 handlers: " << o1->h << std::endl;
		std::cout << "total o3 handlers: " << o3->h << std::endl;
		std::cout << "total o4 handlers: " << o4->h << std::endl;
	)
	da1.resize(0);
	da2.resize(1);
	D_LOG(
		std::cout << "--------------------" << std::endl;
		for (object_handler& oh : da2) {
			std::cout << oh.ID << " " << oh->ID << std::endl;
		}
		std::cout << "total o1 handlers: " << o1->h << std::endl;
		std::cout << "total o3 handlers: " << o3->h << std::endl;
		std::cout << "total o4 handlers: " << o4->h << std::endl;
	)
	D_LOG(
		std::cout << constexpr_strcmp("hello world!", "hello world") << std::endl;	//output should be "!"
		std::cout << constexpr_strlen("hello world") << std::endl;					//output should be "11"
		const char* start_text = "text";
		const char* copied_text = constexpr_strcpy(start_text);
		std::cout << copied_text << std::endl;										//output should be "text"
		delete[] copied_text;
		std::cout << constexpr_substr_num("text1;text2;text3", ";") << std::endl;	//output should be "2"
		std::cout << type(constexpr_strcpy("abc"), 0).name << std::endl;			//output should be "abc"
	)
	uint32_t iiiii[] = { 1, 2, 3, 4 };
	dynamic_array<uint64_t> daf(iiiii);
	std::cout << "dt: " << et.get_dt() << "ms" << std::endl;
}