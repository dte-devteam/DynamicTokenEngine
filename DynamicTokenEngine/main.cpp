#include "tests.h"
#include "core/include/root_scope.h"
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

#include <windows.h>

int main(int argc, char* argv[]) {
	test();
	std::cout << argc << " : : " << (argc > 1 ? argv[1] : argv[0]) << std::endl;
	//Sleep(10000);
	stream::stream s(nullptr, 0);	//to do main function
	s.callstack = new std::stack<uint64_t>();
	dte_core::init_root_scope(0, 0, 0, &s);
	return 0;
}