#include "tests.h"
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

static data::smart_pointer<data::scope> root = nullptr;

int main() {
	test();



	return 0;
}