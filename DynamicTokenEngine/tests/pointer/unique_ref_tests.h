#pragma once
#include "utils/include/pointer/unique_ref.h"
#include "../data_examples.h"
using namespace dte_utils;
namespace test {
	//constructors
	void test_unique_pointer_constructor() {
		std::cout << "---test_unique_pointer_constructor---" << std::endl;
		unique_ref<primitive_test_struct> ur(new primitive_test_struct());
	}
	void test_unique_by_assign_rvalue_unique() {
		std::cout << "---test_unique_by_assign_rvalue_unique---" << std::endl;
		unique_ref<primitive_test_struct> ur;
		ur = unique_ref<primitive_test_struct>(new primitive_test_struct());
	}
	void test_unique_ref() {
		//constructors
		test_unique_pointer_constructor();
		//assign operators
		test_unique_by_assign_rvalue_unique();
		//no need for interaction operators: same code in weak_ref
	}
}