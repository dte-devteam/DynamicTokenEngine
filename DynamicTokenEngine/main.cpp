#include <iostream>
#include <chrono>
#include "tests.h"

#include "token/data/include/value.h"
#include "token/data/include/complex_type.h"
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
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>,
	(data::create_value_function)data::create<float>
};
void func() {
	data::type<float>* types = new data::type<float>[10];
	data::complex_type ect = data::NEW_COMPLEX_TYPE(10, types, v_create, 1);
	size_t _i = 0;
	while (_i < ect.get_number_of_fields()) {
		std::cout << (*ect)[_i++].first.get_name() << std::endl;
	}
	data::type<int>* types2 = new data::type<int>[5];
	data::complex_type ect2 = ect.generate_child(5, types2, v_create, 2);
	_i = 0;
	std::cout << ect2.get_number_of_fields() << std::endl;
	while (_i < ect2.get_number_of_fields()) {
		std::cout << (*ect2)[_i++].first.get_name() << std::endl;
	}
}
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
	std::cout << fv1->get_type().get_name() << std::endl;

	module_version mv = module_version(123, MAX_MODULE_VERSION);
	std::cout << mv.getID() << std::endl;

	func();

	data::type<void> tt;
	std::cout << tt.get_name() << std::endl;

    return 0;
}