#include <iostream>
#include <chrono>
#include "tests.h"

#include "token/data/include/complex_value.h"
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

std::pair<data::create_value_function, data::copy_value_function> v_create_and_copy[] = {
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<int>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>(),
	data::create_copy_value_pair<float>()
};

void func1() {
	data::type<float>* ftp = new data::type<float>[10];
	data::complex_type ct(10, ftp, v_create_and_copy, 321);
	delete[] ftp; //complex_type is independant
	std::cout << ct.getID() << " " << ct.get_number_of_fields() << std::endl;
	data::complex_type ct2(ct);
	std::cout << ct2.getID() << " " << ct2.get_number_of_fields() << std::endl;
	std::cout << (*ct2)->first.get_name() << std::endl;
	data::complex_type ct3(ct, ct2, 4321);
	std::cout << ct3.getID() << " " << ct3.get_number_of_fields() << std::endl;
	std::cout << (*ct3)[10].first.get_name() << std::endl;
	//ok^^^
	data::complex_value cv(ct, 54321);
	std::cout << (*cv)[1]->getID() << " " << ((data::value<char>*)(*cv)[1])->get_type().get_name() << std::endl;
	std::cout << (*cv)[2]->getID() << " " << ((data::value<char>*)(*cv)[2])->get_type().get_name() << std::endl;
	//fucking yes, finnaly no problems!!!^^^
	data::complex_type ctcopy = ct;
	std::cout << ctcopy.getID() << " " << ctcopy.get_number_of_fields() << std::endl;
	//ok^^^
	data::complex_value cv2(cv);
	std::cout << (*cv2)[1]->getID() << " " << ((data::value<char>*)(*cv2)[1])->get_type().get_name() << std::endl;
	std::cout << (*cv2)[2]->getID() << " " << ((data::value<char>*)(*cv2)[2])->get_type().get_name() << std::endl;
	//ok^^^
}
int main() {
	float f = 1.5f;
	int i = 1000;

	data::value<float>* fv1 = (data::value<float>*)v_create_and_copy[1].first(1000);
	**((data::value<int>*)fv1) = i;
	std::cout << **fv1 << " " << fv1->getID() << std::endl;
	std::cout << fv1->get_type().get_name() << std::endl;

	data::value<float>* fv2 = (data::value<float>*)v_create_and_copy[1].first(2000);
	**fv2 = f;
	std::cout << **fv2 << " " << fv2->getID() << std::endl;

	**fv1 = **fv2;
	std::cout << **fv1 << " " << fv1->getID() << " " << **fv2 << " " << fv2->getID() << std::endl;
	std::cout << fv1->get_type().get_name() << std::endl;

	object* fv3 = v_create_and_copy[1].first(3000);
	**((data::value<float>*)fv3) = f;
	std::cout << **((data::value<float>*)fv3) << " " << fv3->getID() << std::endl;

	module_version mv = module_version(123, MAX_MODULE_VERSION);
	std::cout << mv.getID() << std::endl;

	func1();

	data::value<char>* vc = (data::value<char>*)data::copy_value<float>(fv1, fv1->getID());
	std::cout << vc->get_type().get_name() << std::endl;
	std::cout << **(data::value<float>*)vc << " " << vc->getID() << std::endl;
    return 0;
}