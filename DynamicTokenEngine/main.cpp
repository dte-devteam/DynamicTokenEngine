#include "tests/test.h"
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

int main(int argc, char* argv[]) {
	while (--argc) {
		std::cout << argc << " : " << argv[argc] << std::endl;
	}
	run_tests();
	std::cin.get();
}