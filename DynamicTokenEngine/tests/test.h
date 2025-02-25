#pragma once
#include <iostream>
#include "utils/include/dynamic_memory.h"
#include "utils/include/pointer.h"
#include "data_examples.h"
using namespace test;
using namespace dte_utils;
void f() {
	A* a = new A[10];
	dynamic_stack<A> d(a, 10, 0);
	delete[] a;
	ab_visor.log();
	d.resize_allocated(20);;
	ab_visor.log();
}
void run_tests() {
	weak_ref<A[]> wr;
	wr = weak_ref<A[10]>();
	const int len = 10;
	float ia[len];
	for (int i = 0; i < len; ++i) {
		ia[i] = static_cast<float>(i);
	}
	dynamic_stack<int> da{ ia };
	for (const int& i : da) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	A fa[len];
	copy_array(fa, ia, len);
	for (const A& i : fa) {
		std::cout << i.f << " ";
	}
	std::cout << std::endl;



	dynamic_stack<float> dd(ia);
	for (const float& i : dd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	dynamic_stack<int> ddd(dd);
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	ddd = dd;
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
	ddd.resize_allocated(5);
	ddd.push_back(6);
	ddd.push_back(8);
	ddd.push_back(10);
	ddd.push_back(12.0F);
	ddd.push_back(14);
	ddd.push_back(16);
	ddd += dd;
	//ddd = ddd + dd;
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	dynamic_stack<A*> dddd{ 10 };
	dddd = dynamic_stack<void*>();

	ab_visor.reset();
	f();
	ab_visor.log();
	
	M* m = malloc_t<M>(10);
	m[0].i = 1;
	m[1].i = 2;
	m[2].i = 3;
	for (size_t i = 0; i < 10; ++i) {
		std::cout << m[i].i << " ";
	}
	std::cout << std::endl;
	move_array(m + 5, m, 3);

	for (size_t i = 0; i < 10; ++i) {
		std::cout << m[i].i << " ";
	}
	std::cout << std::endl;

	free(m);



	dynamic_stack<M> _d{ 10 };
	dynamic_stack<M> _dd{ _d };
	//_dd[0].i = 1;
	//_dd[0].i = 2;
	//_dd[0].i = 3;
	//_dd.us = 3;
	//_dd = _dd + _dd;

	//for (const M& i : _dd) {
	//	std::cout << i.i << " ";
	//}
	//std::cout << std::endl;
	

	copy_array((float*)0, (const int*)0, 0);
}