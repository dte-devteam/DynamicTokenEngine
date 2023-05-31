#include <iostream>
#include <chrono>
#include "tests.h"

#include "token/data/include/value.h"
using namespace tokenoperator::dte_token;

#include "module/include/module_version.h"
using namespace tokenoperator::dte_module;

/*
* future structure:
* lib(functions)-------->dll(any module, may be multiple)
*   ↓                     ↓
* lib(static instances)->exe
*/
std::chrono::milliseconds timespan(5000);

data::create_value_function v_create[] = {
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>,
	(data::create_value_function)data::create_value<float>
};
void func1() {

}
int main() {
	float f = 1.5f;
	int i = 1000;

	data::value<float>* fv1 = (data::value<float>*)v_create[1](1000);
	**((data::value<int>*)fv1) = i;
	std::cout << **fv1 << " " << fv1->getID() << std::endl;
	std::cout << fv1->get_type().get_name() << std::endl;

	data::value<float>* fv2 = (data::value<float>*)v_create[1](2000);
	**fv2 = f;
	std::cout << **fv2 << " " << fv2->getID() << std::endl;

	**fv1 = **fv2;
	std::cout << **fv1 << " " << fv1->getID() << " " << **fv2 << " " << fv2->getID() << std::endl;
	std::cout << fv1->get_type().get_name() << std::endl;

	object* fv3 = v_create[1](3000);
	**((data::value<float>*)fv3) = f;
	std::cout << **((data::value<float>*)fv3) << " " << fv3->getID() << std::endl;

	module_version mv = module_version(123, MAX_MODULE_VERSION);
	std::cout << mv.getID() << std::endl;

	func1();

    return 0;
}