#pragma once
#include "memory/include/object.h"
namespace test {
	using namespace memory::object;
	enum testmode {
		INITMEM = 0,
		TERMMEM = 1,
		LOG = 2,
		RESIZEBIG = 3,
		RESIZESMALL = 4,
		ADD_OBJ_1 = 5
	};
	static vector<size_t>* sizes = new std::vector<size_t>({
		sizeof(void*),	//8
		sizeof(int),	//4
		5				//5
	});
	void inline test(int testmode) {
		switch (testmode) {
			case INITMEM:
				memorycontroller::instance(sizes);
				for (typeallocator* typealloc : memorycontroller::instance()->objects) {
					std::cout << std::left << std::setw(6) << "size: ";
					std::cout << std::left << std::setw(7) << typealloc->gettypesize();
					std::cout << std::left << std::setw(8) << "length: ";
					std::cout << typealloc->getlistsize() << std::endl;
				}
				break;
			case TERMMEM:
				delete memorycontroller::instance();
				break;
			case LOG:
				memorycontroller::instance()->objects[0]->log_data();
				break;
			case RESIZEBIG:
				memorycontroller::instance()->objects[0]->setlistsize(15, true);
				break;
			case RESIZESMALL:
				memorycontroller::instance()->objects[0]->setlistsize(5, true);
				break;
			case ADD_OBJ_1:
				memorycontroller::instance()->objects[0]->addobject(1, nullptr);
				break;
			default:
				std::cout << "def" << std::endl;
				break;
		}
	}
}