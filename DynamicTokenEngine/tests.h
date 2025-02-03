#pragma once
#include <iostream>


#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>

//#include "utils/include/dynamic_array.h"
#include "utils/include/pointer.h"

#include <vector>
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/
using namespace dte_utils;



struct test_struct {
	test_struct() {
		std::cout << "constructed" << std::endl;
	}
	~test_struct() {
		std::cout << "destructed" << std::endl;
	}
};
struct ref2r {
	
};
struct ref3r : ref2r {

};
void f(test_struct t[]) {

}
//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

void tabc() {
	weak_ref<ref3r[10]> abc3(new ref3r[10]);
	weak_ref<ref3r[]> abc2(new ref3r[10]);
	weak_ref<ref3r[]> abc4(abc3);
	weak_ref<ref3r> abc5(new ref3r());
	weak_ref<ref2r> abc1(abc5);

	weak_ref<ref3r[10]> abc = weak_ref<ref3r[10]>(
		weak_ref<ref3r[10]>()
	);

	strong_ref<test_struct> sr(new test_struct());
	strong_ref<test_struct[]> sr2(new test_struct[4]);

	unknown_ref<test_struct> ur(new test_struct(), true);
}
void test() {
	tabc();
}