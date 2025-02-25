#pragma once
#include <iostream>
namespace test {
	struct AB_visor {
		int A_constructed;
		int A_destructed;
		int B_constructed;
		int B_destructed;
		void log() {
			std::cout << "A constructed:\t" << A_constructed << std::endl;
			std::cout << "A destructed:\t" << A_destructed << std::endl;
			std::cout << "B constructed:\t" << B_constructed << std::endl;
			std::cout << "B destructed:\t" << B_destructed << std::endl;
		}
		void reset() {
			A_constructed = 0;
			A_destructed = 0;
			B_constructed = 0;
			B_destructed = 0;
		}
	};
	inline AB_visor ab_visor;
	//structs
	struct A {
		float f;
		A(float f) : f(f) {
			++ab_visor.A_constructed;
		}
		A(const A&) {
			++ab_visor.A_constructed;
		}
		A() {
			++ab_visor.A_constructed;
		}
		virtual ~A() {
			++ab_visor.A_destructed;
		}
	};
	struct B : A {
		B() {
			++ab_visor.B_constructed;
		}
		~B() {
			++ab_visor.B_destructed;
		}
	};
	struct M {
		M() : i(222) {}
		M(const M& m) : i(111) {}
		M(M&& m) noexcept : i(m.i) {
		//	m.i = 0;
		//	std::cout << "M moved" << std::endl;
		}
		int i;
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