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
	struct A {
		A() {
			std::cout << "constructed A" << std::endl;
		}
		~A() {
			std::cout << "destructed A" << std::endl;
		}
	};
	struct B : A {
		B() {
			std::cout << "constructed B" << std::endl;
		}
		~B() {
			std::cout << "destructed B" << std::endl;
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