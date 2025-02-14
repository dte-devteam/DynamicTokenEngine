#pragma once
#include "utils/include/pointer/strong_ref.h"
#include "../data_examples.h"
using namespace dte_utils;
namespace test {
	//constructors
	void test_strong_empty_constructor() {
		std::cout << "---test_strong_empty_constructor---" << std::endl;
		strong_ref<primitive_test_struct> sr;
	}
	void test_strong_non_array_constructor() {
		std::cout << "---test_strong_non_array_constructor---" << std::endl;
		strong_ref<primitive_test_struct> sr(new primitive_test_struct());
	}
	void test_strong_array_constructor(size_t count) {
		std::cout << "---test_strong_array_constructor---" << std::endl;
		strong_ref<primitive_test_struct[]> sr(new primitive_test_struct[count]);
	}
	void test_strong_by_lvalue_weak() {
		std::cout << "---test_strong_by_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct> wr(new primitive_test_struct());
		strong_ref<primitive_test_struct> sr(wr);
	}
	void test_strong_by_rvalue_weak() {
		std::cout << "---test_strong_by_rvalue_weak---" << std::endl;
		strong_ref<primitive_test_struct> sr(
			weak_ref<primitive_test_struct>(new primitive_test_struct())
		);
	}
	void test_strong_by_lvalue_strong() {
		std::cout << "---test_strong_by_lvalue_strong---" << std::endl;
		strong_ref<primitive_test_struct> sr0(new primitive_test_struct());
		strong_ref<primitive_test_struct> sr1(sr0);
	}
	void test_strong_by_rvalue_strong() {
		std::cout << "---test_strong_by_rvalue_strong---" << std::endl;
		strong_ref<primitive_test_struct> sr(
			strong_ref<primitive_test_struct>(new primitive_test_struct())
		);
	}
	void test_strong_by_incompatible_lvalue_weak() {
		std::cout << "---test_strong_by_incompatible_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct[2]> wr(new primitive_test_struct[2]);
		strong_ref<primitive_test_struct[5]> sr(wr);
	}
	void test_strong_by_incompatible_rvalue_weak() {
		std::cout << "---test_strong_by_incompatible_rvalue_weak---" << std::endl;
		strong_ref<primitive_test_struct[5]> sr(
			weak_ref<primitive_test_struct[2]>(new primitive_test_struct[2])
		);
	}
	void test_strong_by_incompatible_lvalue_strong() {
		std::cout << "---test_strong_by_incompatible_lvalue_strong---" << std::endl;
		strong_ref<primitive_test_struct[2]> sr0(new primitive_test_struct[2]);
		strong_ref<primitive_test_struct[5]> sr1(sr0);
	}
	void test_strong_by_incompatible_rvalue_strong() {
		std::cout << "---test_strong_by_incompatible_rvalue_strong---" << std::endl;
		strong_ref<primitive_test_struct[5]> sr(
			strong_ref<primitive_test_struct[2]>(new primitive_test_struct[2])
		);
	}
	//assign operators
	void test_strong_by_assign_instance() {
		std::cout << "---test_strong_by_assign_instance---" << std::endl;
		strong_ref<primitive_test_struct[]> sr(new primitive_test_struct[2]);
		sr = new primitive_test_struct[2];
	}
	void test_strong_by_assign_lvalue_weak() {
		std::cout << "---test_strong_by_assign_lvalue_weak---" << std::endl;
		weak_ref<primitive_test_struct[]> wr(new primitive_test_struct[2]);
		strong_ref<primitive_test_struct[2]> sr;
		sr = wr;
	}
	void test_strong_by_assign_rvalue_weak() {
		std::cout << "---test_strong_by_assign_rvalue_weak---" << std::endl;
		strong_ref<primitive_test_struct[2]> sr;
		sr = weak_ref<primitive_test_struct[]>(new primitive_test_struct[2]);
	}
	void test_strong_by_assign_lvalue_strong_ref() {
		std::cout << "---test_strong_by_assign_lvalue_strong_ref---" << std::endl;
		strong_ref<primitive_test_struct[]> sr0(new primitive_test_struct[2]);
		strong_ref<primitive_test_struct[2]> sr1;
		sr1 = sr0;
	}
	void test_strong_by_assign_rvalue_strong_ref() {
		std::cout << "---test_strong_by_assign_rvalue_strong_ref---" << std::endl;
		strong_ref<primitive_test_struct[]> sr(new primitive_test_struct[2]);
		sr = strong_ref<primitive_test_struct[2]>(new primitive_test_struct[2]);
	}
	//main tests
	void test_strong_ref() {
		std::cout << "---test_strong_ref---" << std::endl;
		//constructors
		test_strong_empty_constructor();
		test_strong_non_array_constructor();
		test_strong_array_constructor(3);
		test_strong_by_lvalue_weak();
		test_strong_by_rvalue_weak();
		test_strong_by_lvalue_strong();
		test_strong_by_rvalue_strong();
		test_strong_by_incompatible_lvalue_weak();
		test_strong_by_incompatible_rvalue_weak();
		test_strong_by_incompatible_lvalue_strong();
		test_strong_by_incompatible_rvalue_strong();
		//assign operators
		test_strong_by_assign_instance();
		test_strong_by_assign_lvalue_weak();
		test_strong_by_assign_rvalue_weak();
		test_strong_by_assign_lvalue_strong_ref();
		test_strong_by_assign_rvalue_strong_ref();
	}
}