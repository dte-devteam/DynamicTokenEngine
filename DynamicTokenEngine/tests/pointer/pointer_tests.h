#pragma once
#include "weak_ref_tests.h"
#include "strong_ref_tests.h"
#include "unknown_ref_tests.h"
#include "unique_ref_tests.h"
namespace test {
	void test_pointer() {
		//test_weak_ref();
		//test_strong_ref();
		//test_unknown_ref();
		//test_unique_ref();

		//unknown_ref<int> sr0 = weak_ref<int>();
		//strong_ref<int> sr1{ unknown_ref<int>() };
		//sr0 = sr1;
/*
		weak_ref<A> wr0{ new B() };
		weak_ref<int> wr1{ new int };
		weak_ref<int> wr2{ weak_ref<int>()};
		wr0 = new B();
		wr0 = weak_ref<A>();
		wr0 = weak_ref<B>();
		wr0 = nullptr;
		strong_ref<int> sr0{ weak_ref<int>()};
		wr1 = sr0;

		unknown_ref<int> ur0{};
		unknown_ref<int> ur1{ ur0 };
		unknown_ref<int> ur2{ sr0 };
		ur2 = sr0;*/


		//unknown_ref<A> ur3{new A(), true};
		//unknown_ref<A> ur4;
		//ur3 = ur4;
		unknown_ref<A> ur5(new A(), true);
		//std::cout << ur5.get_strong_owners();
		ur5 = strong_ref<A>(new A());
		strong_ref<A> sr1;
		//sr1 = unknown_ref<A>(new B, true);
		//sr1 = strong_ref<A>(new B);
		//weak_ref<A> wrrr(new B);
		//sr1 = strong_ref<B>(new B);

		sr1 = unknown_ref<A>(new A, true);

		sr1 = weak_ref<A>(new A);

		ur5 = weak_ref<A>(new A);

		ur5 = unknown_ref<B>(new B, true);	
	}
}
