#pragma once
#include <iostream>

#include "module/include/module_instance.h"

#include "utils/include/exec_time.h"
#include "utils/include/pointer.h"
#include "utils/include/hash.h"

#include "token/include/data.h"
#include "token/include/token.h"
#include "token/include/function.h"

#include "core/include/initialization_data.h"

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
struct S_L : S_LOG {
	int i;
};
struct S {
	int i;
};
using namespace dte_token;
using namespace dte_module;
using namespace dte_utils;
using namespace dte_core;
//using namespace dte_parser;
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
	//should be 11, 0, 0, 1, 3, 5, 7, 0, 0, 0, 1, 3, 5, 7, 9, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "insert index -3 at index 15" << std::endl;
	dyt.insert(15, *(dyt.end() - 3));
	//should be 11, 0, 0, 1, 3, 5, 7, 0, 0, 0, 1, 3, 5, 7, 9, 7, 11
	std::cout << "list \'dyt\': ";
	for (size_t _i : dyt) {
		std::cout << _i << " ";
	}
	std::cout << std::endl;
	std::cout << "--function \'test_dynamic_array\' ended---" << std::endl;
}
inline void test_strings() {
	std::cout << "----function \'test_strings\' started-----" << std::endl;
	dynamic_string ds1("abc1");
	dynamic_string ds2("abc2");
	dynamic_string ds3;
	ds3 = ds1 + ds2;
	std::cout << ds3.begin() << std::endl;
	ds3 = ds1 + "abc3";
	std::cout << ds3.begin() << std::endl;
	ds3 = "abc0" + ds1;
	std::cout << ds3.begin() << std::endl;
	ds3 = "abc0" + dynamic_string("abc-10");
	std::cout << ds3.begin() << std::endl;
	std::cout << "-----function \'test_strings\' ended------" << std::endl;
}
inline void test_pointer() {
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
	std::cout << "unknown_ref (as strong): " << std::endl;
	delete new unknown_ref<S_LOG, false>(true, new S_LOG());
	//unknown_ref<int, false> z = unknown_ref<int, false>::unknown_ref<false>();
	std::cout << "-----function \'test_pointers\' ended-----" << std::endl;
}
inline void test_function() {
	std::cout << "----function \'test_function\' started----" << std::endl;
	func_args stack;
	dynamic_function df;
	token* th = new token();
	strong_ref<function, false> add_ref(add);
	th->d = strong_ref<int, false>(new int(123));
	df.steps.emplace_back(
		0,
		0,
		weak_ref<function>(),
		strong_ref<token, false>(th)
	);
	th = new token();
	th->d = strong_ref<int, false>(new int(321));
	df.steps.emplace_back(
		0,
		0,
		weak_ref<function>(),
		strong_ref<token, false>(th)
	);
	df.steps.emplace_back(
		0,
		0,
		weak_ref<function>(add_ref),
		strong_ref<token, false>()
	);
	hpet et;
	df.execute(stack);
	std::cout << "dt: " << et.get_ns_dt_strong().count() << "ns" << std::endl;
	std::cout << "result: " << *(int*)stack[0]->d.get_pointer() << std::endl;
	std::cout << "-----function \'test_function\' ended-----" << std::endl;
}
inline void test() {
	hpet et;
	test_dynamic_array();
	std::cout << "dt: " << et.get_ns_dt_strong().count() << "ns" << std::endl;
	test_strings();
	std::cout << "dt: " << et.get_ns_dt_strong().count() << "ns" << std::endl;
	test_pointer();
	std::cout << "dt: " << et.get_ns_dt_strong().count() << "ns" << std::endl;
	test_function();
	std::cout << "dt: " << et.get_ns_dt_strong().count() << "ns" << std::endl;
	try {
		weak_ref<int>& r = any_ref<int>().get<weak_ref>();
	}
	catch (const std::exception& e) {
		printf("Error: %s\n", e.what());
	}
	std::cout << static_cast<size_t>(pearson_hash<wchar_t, wchar_t, wchar_t>(L"\2\1", 2)) << std::endl;
	std::cout << (size_t)(L"\2"[0]) << std::endl;
}