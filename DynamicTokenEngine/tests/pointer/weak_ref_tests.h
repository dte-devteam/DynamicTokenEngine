#pragma once
#include "utils/include/pointer/weak_ref.h"
#include "../data_examples.h"
using namespace dte_utils;
namespace test {
	/*
	//constructors
	void test_weak_empty_constructor() {
		std::cout << "---test_weak_empty_constructor---" << std::endl;
		weak_ref<primitive_test_struct> wr;
	}
	void test_weak_non_array_constructor(primitive_test_struct* non_array_pts) {
		std::cout << "---test_weak_non_array_constructor---" << std::endl;
		weak_ref<primitive_test_struct> wr(non_array_pts);
	}
	void test_weak_array_constructor(primitive_test_struct* array_pts) {
		std::cout << "---test_weak_array_constructor---" << std::endl;
		weak_ref<primitive_test_struct[]> sr(array_pts);
	}
	void test_weak_by_lvalue_weak() {
		std::cout << "---test_weak_by_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct> wr0;
		weak_ref<primitive_test_struct> wr1{ wr0 };
	}
	void test_weak_by_rvalue_weak() {
		std::cout << "---test_weak_by_rvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct> wr{
			weak_ref<primitive_test_struct>()
		};
	}
	void test_weak_by_incompatible_lvalue_weak() {
		std::cout << "---test_weak_by_incompatible_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct[2]> wr0;
		weak_ref<primitive_test_struct[5]> wr1{ wr0 };
	}
	void test_weak_by_incompatible_rvalue_weak() {
		std::cout << "---test_weak_by_incompatible_rvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct[5]> wr{
			weak_ref<primitive_test_struct[2]>()
		};
	}
	//assign operators
	void test_weak_by_assign_instance(primitive_test_struct* non_array_pts, primitive_test_struct* array_pts) {
		std::cout << "---test_weak_by_assign_instance---" << std::endl;
		weak_ref<primitive_test_struct> wr0;
		weak_ref<primitive_test_struct[]> wr1;
		wr0 = non_array_pts;
		wr1 = array_pts;
	}
	void test_weak_by_assign_lvalue_weak() {
		std::cout << "---test_weak_by_assign_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct> wr0;
		weak_ref<primitive_test_struct> wr1;
		wr0 = wr1;
	}
	void test_weak_by_assign_rvalue_weak() {
		std::cout << "---test_weak_by_assign_rvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct> wr;
		wr = weak_ref<primitive_test_struct>();
	}
	void test_weak_by_child() {
		std::cout << "---test_weak_by_child---" << std::endl;
		weak_ref<A> wr;
		wr = weak_ref<B>();
		wr = new B();
		delete wr.get_pointer();
	}
	//interaction operators
	void test_weak_by_ref_operator(primitive_test_struct* non_array_pts) {
		std::cout << "---test_weak_by_ref_operator---" << std::endl;
		weak_ref<primitive_test_struct> wr(non_array_pts);
		wr->int_field = (*wr).int_field;
	}
	void test_weak_by_array_operator(primitive_test_struct* array_pts) {
		std::cout << "---test_weak_by_array_operator---" << std::endl;
		weak_ref<primitive_test_struct[]> wr(array_pts);
		wr[0].int_field = wr[1].int_field;
	}
	void test_weak_by_func_operator() {
		std::cout << "---test_weak_by_func_operator---" << std::endl;
		weak_ref<function> wr(return_1);
		std::cout << wr() << std::endl;
	}
	//main tests
	void test_weak_ref() {
		std::cout << "---test_weak_ref---" << std::endl;
		primitive_test_struct* non_array_pts = new primitive_test_struct();
		primitive_test_struct* array_pts = new primitive_test_struct[2];
		//constructors
		test_weak_empty_constructor();
		test_weak_non_array_constructor(non_array_pts);
		test_weak_array_constructor(array_pts);
		test_weak_by_lvalue_weak();
		test_weak_by_rvalue_weak();
		test_weak_by_incompatible_lvalue_weak();
		test_weak_by_incompatible_rvalue_weak();
		//assign operators
		test_weak_by_assign_instance(non_array_pts, array_pts);
		test_weak_by_assign_lvalue_weak();
		test_weak_by_assign_rvalue_weak();
		test_weak_by_child();
		//interaction operators
		test_weak_by_ref_operator(non_array_pts);
		test_weak_by_array_operator(array_pts);
		test_weak_by_func_operator();
		delete non_array_pts;
		delete[] array_pts;
	}*/
}