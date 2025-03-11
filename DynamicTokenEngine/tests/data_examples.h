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
			std::cout << "A(float)\t" << std::endl;
		}
		A(const A& a) : f(a.f) {
			++ab_visor.A_constructed;
			std::cout << "A copied\t" << std::endl;
		}
		A(A&& a) noexcept : f(a.f) {
			++ab_visor.A_constructed;
			std::cout << "A moved\t" << std::endl;
		}
		A() : f(-1.0F) {
			++ab_visor.A_constructed;
			std::cout << "A()\t" << std::endl;
		}
		virtual ~A() {
			++ab_visor.A_destructed;
		}

		A& operator =(const A& a) {
			std::cout << "A = const A&\t" << std::endl;
			f = a.f;
			return *this;
		}
		A& operator =(A&& a) noexcept {
			std::cout << "A = A&&\t" << std::endl;
			std::swap(f, a.f);
			return *this;
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
	struct UM {
		UM() {}
		UM(const UM&) {}
		UM(UM&& m) = delete;
	};
	struct UC {
		UC() {}
		UC(const UC& m) = delete;
		UC(UC&&) {}
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