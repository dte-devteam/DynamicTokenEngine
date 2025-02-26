#pragma once
#include <iostream>
#include "utils/include/dynamic_memory.h"
#include "utils/include/pointer.h"
#include "data_examples.h"
#include <vector>
using namespace test;
using namespace dte_utils;
void f1() {
	A* a = new A[10];
	dynamic_stack<A> d(a, 10, 0);
	delete[] a;
	ab_visor.log();
	d.resize_allocated(20);;
	ab_visor.log();
}
void f2() {
	weak_ref<A[]> wr;
	wr = weak_ref<A[10]>();
}
void run_tests() {
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
	//dddd = dynamic_stack<void*>();

	ab_visor.reset();
	f1();
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



	




	dynamic_stack<B> ds;
	dynamic_stack<A> ds2{ ds };

	ds2.push_back(A());


	

	dynamic_stack<float> ds4{ 100 };
	ds4.push_back(1);
	ds4.push_back(2);
	ds4.push_back(3);

	dynamic_stack<int> ds3;
	ds3.push_back(1.0F);
	ds3 = ds3 + ds3 + ds3 + ds4;
	ds3 = ds3 + dynamic_stack<float>();

	for (const int& i : ds3) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
	M* mm = new M[3];
	mm[0].i = 1;
	mm[1].i = 2;
	mm[2].i = 3;
	dynamic_stack<M> dsm(mm, 3, 0);
	dsm.push_back(M());//OK
	delete[] mm;
	//dsm += dsm; wont cause problem
	dsm = dsm + dsm; //motherfucker
	for (const M& i : dsm) {
		std::cout << i.i << " ";
	}
	dsm.push_back(M());//heap problems
}