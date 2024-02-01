#include "tests.h"

#include "core/include/type_assembler.h"
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)





using namespace dte_token;
using namespace dte_utils;
using namespace dte_core;
int main(int argc, char* argv[]) {
	while (--argc) {
		std::cout << argc << " : " << argv[argc] << std::endl;
	}
	test();
	//core init script
	//type_assembler::get_instance().register_type();
	//read first dte file
	std::cin.get();
}