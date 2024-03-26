#pragma once
#include <iostream>
#include "token/include/object.h"
#include "token/include/type.h"
#include "token/include/function.h"

#include "module/include/module_instance.h"

#include "utils/include/exec_time.h"
#include "utils/include/pointer.h"

#include "utils/include/debug_defines.h"

#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>


#include <vector>
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

struct S_LOG {
	S_LOG() {
		std::cout << "S_LOG is constructed" << std::endl;
	}
	~S_LOG() {
		std::cout << "S_LOG is destructed" << std::endl;
	}
};
using namespace dte_token;
using namespace dte_module;
using namespace dte_utils;
inline void test_dynamic_array() {
	std::cout << "-function \'test_dynamic_array\' started--" << std::endl;
	size_t ints[] = {
		1, 3, 5, 7, 9, 11
	};
	std::cout << "create array \'dyt\' of " << STR_DECL_TYPE(ints) << std::endl;
	dynamic_array<size_t> dyt(ints);
	//should be 1, 3, 5, 7, 9, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "insert 0 into \'dyt\' 5 times at index 0" << std::endl;
	dyt.insert(0, 0, 5);
	//should be 0, 0, 0, 0, 0, 1, 3, 5, 7, 9, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "insert from index 5 to index -2 at index 2" << std::endl;
	dyt.insert(2, dyt.begin() + 5, dyt.end() - 2);
	//should copy 1, 3, 5, 7
	//should be 0, 0, 1, 3, 5, 7, 0, 0, 0, 1, 3, 5, 7, 9, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "insert index -1 at index 0" << std::endl;
	dyt.insert(0, *dyt.back());
	//should be 11, 0, 0, 0, 1, 3, 5, 7, 0, 0, 0, 1, 3, 5, 7, 9, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "insert index -3 at index 15" << std::endl;
	dyt.insert(15, *(dyt.end() - 3));
	//should be 11, 0, 0, 0, 1, 3, 5, 7, 0, 0, 0, 1, 3, 5, 7, 9, 7, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "--function \'test_dynamic_array\' ended---" << std::endl;
}
inline void test_pointers() {
	std::cout << "----function \'test_pointers\' started----" << std::endl;
	//test weak_ref
	int weak_ints[] = { 1, 2, 3, 4, 5 };
	weak_ref<decltype(weak_ints)> wr0(&weak_ints);
	std::cout << "accessing " << STR_DECL_TYPE(weak_ints) << " through \'weak_ref\': ";
	for (size_t i = 0; i < ARRAYSIZE(weak_ints); ++i) {
		std::cout << (*wr0)[i] << " ";
	}
	std::cout << std::endl;
	//test strong_ref 
	//warning! sr<n> is controlled by new and delete for proper log
	strong_ref<S_LOG, false>* sr0 = new strong_ref<S_LOG, false>(new S_LOG());
	delete sr0; std::cout << "sr0 is destructed" << std::endl;
	sr0 = new strong_ref<S_LOG, false>(new S_LOG());
	strong_ref<S_LOG, false>* sr1 = new strong_ref<S_LOG, false>(*sr0);
	std::cout << "sr1 strong owners: " << sr1->get_strong_owners() << std::endl;
	std::cout << "sr1 weak owners: " << sr1->get_weak_owners() << std::endl;
	delete sr0; std::cout << "sr0 is destructed" << std::endl;
	std::cout << "sr1 strong owners: " << sr1->get_strong_owners() << std::endl;
	std::cout << "sr1 weak owners: " << sr1->get_weak_owners() << std::endl;
	delete sr1; std::cout << "sr1 is destructed" << std::endl;
	//test strong_ref-weak_ref relationship
	//warning! wr<n> is controlled by new and delete for proper log
	sr0 = new strong_ref<S_LOG, false>(new S_LOG());
	weak_ref<S_LOG>* wr1 = new weak_ref<S_LOG>(*sr0);
	std::cout << "sr0 strong owners: " << sr0->get_strong_owners() << std::endl;
	std::cout << "sr0 weak owners: " << sr0->get_weak_owners() << std::endl;
	delete wr1; std::cout << "wr1 is destructed" << std::endl;
	std::cout << "sr0 strong owners: " << sr0->get_strong_owners() << std::endl;
	std::cout << "sr0 weak owners: " << sr0->get_weak_owners() << std::endl;
	wr1 = new weak_ref<S_LOG>(*sr0);
	delete sr0; std::cout << "sr0 is destructed" << std::endl;
	std::cout << "wr1 strong owners: " << wr1->get_strong_owners() << std::endl;
	std::cout << "wr1 weak owners: " << wr1->get_weak_owners() << std::endl;
	delete wr1; std::cout << "wr1 is destructed" << std::endl;
	std::cout << "-----function \'test_pointers\' ended-----" << std::endl;
}
inline void test() {
	/*
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
	dynamic_array<object_handler> da1(ops);
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
	container c = container(new uint32_t[]{1,1,1,1}, true);
	*/


	/*
	hpet et;
	size_t iter_num = et.get_creation_time() / 10;
	std::cout << iter_num << std::endl;
	for (size_t _l = 10; _l; --_l) {
		dynamic_array<size_t> dyt(0,0,iter_num);
		for (size_t _i = iter_num; _i; --_i) {
			dyt.push_back((_i * 3) % 5);
		}
		std::cout << "dt a: " << et.get_dt() << "ms" << std::endl;
	}
	for (size_t _l = 10; _l; --_l) {
		std::vector<size_t> vt(iter_num);
		for (size_t _i = iter_num; _i; --_i) {
			vt.push_back((_i * 3) % 5);
		}
		std::cout << "dt v: " << et.get_dt() << "ms" << std::endl;
	}
	*/
	test_dynamic_array();
	test_pointers();
	//std::cout << "dt: " << et.get_dt() << "ms" << std::endl;
}
