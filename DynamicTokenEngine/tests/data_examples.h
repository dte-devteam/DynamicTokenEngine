#pragma once
#include <iostream>
namespace test {
	//structs
	struct primitive_test_struct {
		int int_field;
		primitive_test_struct() {
			std::cout << "constructed" << std::endl;
		}
		~primitive_test_struct() {
			std::cout << "destructed" << std::endl;
		}
	};
	//functions
	typedef int (*function)();
	int return_1() {
		return 1;
	}
	int return_2() {
		return 2;
	}
}