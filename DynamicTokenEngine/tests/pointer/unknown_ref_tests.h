#pragma once
#include "utils/include/pointer/unknown_ref.h"
#include "../data_examples.h"
using namespace dte_utils;
namespace test {
	/*
	//constructors
	void test_unknown_empty_constructor() {
		std::cout << "---test_unknown_empty_constructor---" << std::endl;
		unknown_ref<primitive_test_struct> ur0;
		unknown_ref<primitive_test_struct> ur1(true);
	}
	void test_unknown_pointer_constructor() {
		std::cout << "---test_unknown_pointer_constructor---" << std::endl;
		unknown_ref<primitive_test_struct> ur0(new primitive_test_struct(), false);
		unknown_ref<primitive_test_struct[]> ur1(new primitive_test_struct[2], true);
		delete ur0.get_pointer();
	}
	void test_unknown_by_lvalue_unknown() {
		std::cout << "---test_unknown_by_lvalue_unknown---" << std::endl;
		unknown_ref<primitive_test_struct> ur0;
		unknown_ref<primitive_test_struct> ur1(ur0, false);
	}
	void test_unknown_by_rvalue_unknown() {
		std::cout << "---test_unknown_by_rvalue_unknown---" << std::endl;
		unknown_ref<primitive_test_struct> ur(
			unknown_ref<primitive_test_struct>(),
			true
		);
	}
	//assign operators
	void test_unknown_by_assign_instance() {
		std::cout << "---test_unknown_by_assign_instance---" << std::endl;
		unknown_ref<primitive_test_struct> ur0;
		unknown_ref<primitive_test_struct> ur1(true);
		ur0 = new primitive_test_struct();
		ur1 = new primitive_test_struct();
		delete ur0.get_pointer();
	}
	void test_unknown_by_assign_lvalue_unknown() {
		std::cout << "---test_unknown_by_assign_lvalue_unknown---" << std::endl;
		unknown_ref<primitive_test_struct> ur0;
		unknown_ref<primitive_test_struct> ur1(new primitive_test_struct(), true);
		ur0 = ur1;
	}
	void test_unknown_by_assign_rvalue_unknown() {
		std::cout << "---test_unknown_by_assign_rvalue_unknown---" << std::endl;
		unknown_ref<primitive_test_struct> ur;
		ur = unknown_ref<primitive_test_struct>(new primitive_test_struct(), true);
	}
	void test_unknown_by_assign_lvalue_weak() {
		std::cout << "---test_unknown_by_assign_lvalue_weak---" << std::endl;
		unknown_ref<primitive_test_struct> ur(true);
		weak_ref<primitive_test_struct> wr(new primitive_test_struct());
		ur = wr;
	}
	void test_unknown_by_child() {
		std::cout << "---test_unknown_by_child---" << std::endl;
		unknown_ref<A> ur(true);
		ur = weak_ref<B>();
		ur = new B();
	}
	//strength
	void test_unknown_by_strong() {
		std::cout << "---test_unknown_by_strong---" << std::endl;
		unknown_ref<primitive_test_struct> ur(new primitive_test_struct(), false);
		ur.set_strength(true);
	}
	void test_unknown_by_weak() { 
		std::cout << "---test_unknown_by_weak---" << std::endl;
		unknown_ref<primitive_test_struct> ur(new primitive_test_struct(), true);
		ur.set_strength(false);
	}
	//main tests
	void test_unknown_ref() {
		//constructors
		test_unknown_empty_constructor();
		test_unknown_pointer_constructor();
		test_unknown_by_lvalue_unknown();
		test_unknown_by_rvalue_unknown();
		//assign operators
		test_unknown_by_assign_instance();
		test_unknown_by_assign_lvalue_unknown();
		test_unknown_by_assign_rvalue_unknown();
		test_unknown_by_assign_lvalue_weak();
		test_unknown_by_child();
		//strength
		test_unknown_by_strong();
		test_unknown_by_weak();
	}*/
}