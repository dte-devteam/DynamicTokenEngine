#pragma once
#include <iostream>
#include "utils/include/dynamic_memory.h"

#include "token/include/token.h"

#include "utils/include/pointer.h"
#include "utils/include/exec_time.h"
#include "data_examples.h"
using namespace test;
using namespace dte_utils;
using namespace dte_token;
constexpr int len = 10;
void a0() {
	weak_ref<B> wrb;
	weak_ref<A> wra{ wrb };
	wra = wrb;
	wra = weak_ref<B>();
	wra = wra;
	wra = weak_ref<A>();

	wra = strong_ref<A>(new A);
	wra = strong_ref<B>(new B);

	strong_ref<A> sra = strong_ref<A>(weak_ref<B>());
	sra = weak_ref<A>(new A);

	weak_ref<A> wr0((A*)0);
	wr0 = weak_ref<A>((A*)10);
	std::cout << wr0.get_pointer() << std::endl;
}
void f0() {
	std::cout << "|||const strong_ref& = weak_ref&&" << std::endl;
	strong_ref<A> sr(new A);
	sr = weak_ref<A>();
}
void f1() {
	std::cout << "|||const unknown_ref& (strong) = unknown_ref&& (weak)" << std::endl;
	unknown_ref<A> ur(new A, true);
	ur = unknown_ref<A>(false);
}

void f2() {
	std::cout << "|||dynamic_stack<A> resize" << std::endl;
	A* a = new A[10];
	dynamic_stack<A> d(a, 10, 0);
	delete[] a;
	ab_visor.log();
	d.resize_allocated(20);
	ab_visor.log();
}

void f3() {
	std::cout << "|||dynamic_stack with int & float" << std::endl;
	float ia[len];
	for (int i = 0; i < len; ++i) {
		ia[i] = static_cast<float>(i);
	}
	dynamic_stack<int> da{ ia };
	std::cout << "int {float}" << std::endl;
	for (const int& i : da) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "int {float} + float[]" << std::endl;
	for (const int& i : da + ia) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	dynamic_stack<float> dd(ia);
	std::cout << "float {float}" << std::endl;
	for (const float& i : dd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	dynamic_stack<int> ddd(dd);
	std::cout << "int (float)" << std::endl;
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	ddd = dd;
	std::cout << "int = float" << std::endl;
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "int[10->5]" << std::endl;
	ddd.resize_allocated(5);
	ddd.push_back(6);
	ddd.push_back(8);
	ddd.push_back(10);
	ddd.push_back(12.0F);
	ddd.push_back(14);
	ddd.push_back(16);
	std::cout << "int push 6, 8, 10, 12.0F, 14, 16" << std::endl;
	for (const int& i : ddd) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	ddd.emplace_back(1);
	ddd[5];
}
void f4() {
	std::cout << "|||float -> A" << std::endl;
	float ia[len];
	for (int i = 0; i < len; ++i) {
		ia[i] = static_cast<float>(i);
	}
	A* fa = malloc_t<A>(len);
	array_to_array(fa, ia, len);
	for (size_t i = 0; i < len; ++i) {
		std::cout << fa[i].f << " ";
		fa[i].~A();
	}
	std::cout << std::endl;
	free(fa);
}
void f5() {
	std::cout << "|||A* = B* & A push A()" << std::endl;
	dynamic_stack<B> ds;
	dynamic_stack<A> ds2{ ds };

	ds2.push_back(A());
}
void f6() {
	std::cout << "|||A array (remove)" << std::endl;
	A* aaa = new A[5];
	dynamic_array<A> dasi(aaa, 5, 0);
	ab_visor.log();
	delete[] aaa;
	ab_visor.log();
	dasi[0].f = 1;
	dasi[1].f = 2;
	dasi[2].f = 3;
	dasi[3].f = 4;
	dasi[4].f = 5;
	dasi.remove(dasi.begin() + 4);
	for (const A& i : dasi) {
		std::cout << i.f << " ";
	}
	std::cout << std::endl;
	std::cout << dasi[4].f << std::endl;
}
void f7() {
	std::cout << "|||A array (erase(T*))" << std::endl;
	A* aaa = new A[5];
	dynamic_array<A> dasi(aaa, 5, 10);
	ab_visor.log();
	delete[] aaa;
	ab_visor.log();
	dasi[0].f = 1;
	dasi[1].f = 2;
	dasi[2].f = 3;
	dasi[3].f = 4;
	dasi[4].f = 5;
	const int i = 10;
	//dasi.erase(dasi.begin());
	//dasi.remove(dasi.begin());
	
	//dasi.erase(dasi.begin() + 0, dasi.begin() + 4);
	//dasi.remove(dasi.begin() + 0, dasi.begin() + 4);

	//dasi.insert(dasi.begin() + 3, 100);
	//dasi.insert(dasi.begin() + 3, i, 5);
	//dasi.insert(dasi.begin() + 3, dasi.begin(), dasi.begin() + 3);
	dasi.insert(dasi.begin() + 3, {11, 22, 33});

	dasi.emplace(dasi.begin() + 3, i);
	for (const A& i : dasi) {
		std::cout << i.f << " ";
	}
	std::cout << std::endl;
	std::cout << dasi[4].f << std::endl;

	int f = static_cast<int>(1.0F); 
}
void run_tests() {
	hpet et;



	ab_visor.reset();
	a0();
	ab_visor.log();


	ab_visor.reset();
	f0();
	ab_visor.log();

	ab_visor.reset();
	f1();
	ab_visor.log();

	ab_visor.reset();
	f2();
	ab_visor.log();


	f3();

	ab_visor.reset();
	f4();
	ab_visor.log();

	ab_visor.reset();
	f5();
	ab_visor.log();

	ab_visor.reset();
	f6();
	ab_visor.log();

	ab_visor.reset();
	f7();
	ab_visor.log();


	dynamic_string<char> cstr;// ("");
	cstr += "AB";
	cstr += L"CD";
	std::cout << cstr.begin() << std::endl;

	//dynamic_string<char> cstr1("");

	//cstr1 = cstr1 + L"AB";
	//cstr1 += cstr1; 
	//cstr1 = cstr1 + dynamic_string<wchar_t>(L"CD");
	//std::cout << cstr1.begin() << std::endl;
	//for (const char c : cstr1) {
	//	std::cout << c << std::endl;
	//}


	dynamic_string<char> cstr2("A");
	dynamic_string<char> cstr3("B");
	dynamic_string<char> cstr4 = cstr2 + cstr3;
	std::cout << cstr4.get_used_size() << std::endl;
	std::cout << cstr4.begin() << std::endl;
	std::cout << "*****" << std::endl;
	

	array_to_array((int*)0, (int*)0, 0);
	std::cout << "***total exec time: " << et.get_ms_dt_weak() << "***" << std::endl;
} 