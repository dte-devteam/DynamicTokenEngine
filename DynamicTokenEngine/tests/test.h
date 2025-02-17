#pragma once
#include "pointer/pointer_tests.h"
#include "utils/include/memory.h"
#include "utils/include/dynamic_array.h"
using namespace test;
void run_tests() {
	test_pointer();
	/*
	const size_t len = 16;
	int* var1 = new int[len];
	int* var2 = new int[len];
	float var3[len];
	for (size_t i = 0; i < len; ++i) {
		var1[i] = i;
		var3[i] = i;
	}
	copy_memory(var2, var1, sizeof(int) * len);
	for (size_t i = 0; i < len; ++i) {
		if (var2[i] != i) {
			std::cout << var1[i] << std::endl;
			std::cout << "!" << var2[i] << std::endl;
		}
	}

	dynamic_array<int> da(var1, len, 0);
	dynamic_array<int> da1{ var3 };
	


	for (const int& i : da) {
		std::cout << i << std::endl;
	}
	for (const int& i : da1) {
		std::cout << i << std::endl;
	}

	delete[] var1;
	delete[] var2;
	*/
}