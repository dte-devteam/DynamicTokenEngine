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
	int a;
};

typedef int(*fp)(void);
//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)
int f1() {
	return 1;
}
int f2() {
	return 2;
}

void tabc() {
	weak_ref<ref3r[10]> abc3(new ref3r[10]);
	weak_ref<ref3r[]> abc2(new ref3r[10]);
	weak_ref<ref3r[]> abc4(abc3);
	weak_ref<ref3r> abc5(new ref3r());
	weak_ref<ref2r> abc1(abc5);

	ref3r r = abc3[2];

	abc1 = new ref3r();

	abc5->a = 5;
	(*abc5).a = 5;

	weak_ref<ref3r[10]> abc = weak_ref<ref3r[10]>(
		weak_ref<ref3r[10]>()
	);

	weak_ref<ref3r[]> abc11;
	abc11 = weak_ref<ref3r[]>();
	abc11 = abc3;
	
	weak_ref<ref3r[10][5]> www;
	ref3r* aaa = www[0];


	strong_ref<test_struct> sr(new test_struct());
	strong_ref<test_struct[]> sr2(new test_struct[4]);

	strong_ref<test_struct[10][5]> sr3;
	sr3[0];

	weak_ref<test_struct> wts;
	sr = wts;

	unknown_ref<test_struct> ur(new test_struct(), false);
	ur.set_strength(true);
	ur.set_strength(false);
	
	weak_ref<fp> wr(f1);
	wr = f2;
	std::cout << wr() << std::endl;

}
void tsr() {
	/*
	strong_ref<test_struct[500]> abc;
	strong_ref<test_struct[]> abc2;
	abc = new test_struct[500];
	abc = strong_ref<test_struct[500]>(new test_struct[500]); 
	abc = abc2;*/
}
void test() {
	tabc();
	//for (size_t i = 0; i < 10; ++i) {
	//	tsr();
	//}
	
}