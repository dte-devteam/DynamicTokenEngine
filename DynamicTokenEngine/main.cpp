#include <iostream>
#include <chrono>
#include "tests.h"

#include "token/data/include/value.h"
using namespace tokenoperator::token;
/*
* future structure:
* lib(functions)-------->dll(any module, may be multiple)
*   ↓                     ↓
* lib(static instances)->exe
*/
std::chrono::milliseconds timespan(5000);

typedef object* (*create)(uint64_t);
create v_create[] = {
	(create)data::create<int>,
	(create)data::create<float>
};

int main() {
	float f = 1.5f;
	int i = 1000;

	data::value<float>* fv1 = (data::value<float>*)v_create[1](0);
	**((data::value<int>*)fv1) = i;
	std::cout << **fv1 << " " << fv1->getID() << std::endl;

	data::value<float>* fv2 = (data::value<float>*)v_create[1](1);
	**fv2 = f;
	std::cout << **fv2 << " " << fv2->getID() << std::endl;

	**fv1 = **fv2;
	std::cout << **fv1 << " " << fv1->getID() << " " << **fv2 << " " << fv2->getID() << std::endl;
	std::cout << fv1->t.get_name() << std::endl;
    return 0;
}