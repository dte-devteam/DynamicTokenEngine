#pragma once
#include "memory/include/object.h"
#include "memory/include/function.h"
#include "memory/include/stream.h"
#define ALGEBRA_EXPORTS
#include "add.h"
using namespace memory::object;
using namespace memory::stream;
namespace test {
	enum testmode {
		INITMEM,
		TERMMEM,
		LOG,
		RESIZEBIG,
		RESIZESMALL,
		ADD_OBJ,
		OP_INT_SET_0,
		OP_INT_ADD,
		LOG_INT_OBJ,

		THREAD_CREATE
	};
	static std::vector<size_t>* sizes = new std::vector<size_t>({
		sizeof(void*),	//8
		sizeof(int),	//4
		5				//5
	});
	static stream* s;
	static int a, b, c;
	static uint64_t e = 0;
	void inline test(int testmode) {
		switch (testmode) {
			iterator* i;
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
			case ADD_OBJ:
				memorycontroller::instance()->objects[0]->addobject(1, nullptr);
				break;
			case OP_INT_SET_0:
				i = memorycontroller::instance()->getobject(20, false);
				*(int*)i->getpointer() = 0;
				break;
			case OP_INT_ADD:
				i = memorycontroller::instance()->getobject(20, false);
				*(int*)i->getpointer() = *(int*)i->getpointer() + 1;
				break;
			case LOG_INT_OBJ:
				i = memorycontroller::instance()->getobject(20, false);
				std::cout << *(int*)i->getpointer() << std::endl;
				break;
			case THREAD_CREATE:
				a = 10;
				b = 5;
				s = new stream(&functions::algebra::int_add, 0, nullptr);
				s->execute(new std::vector<void*>({ (void*)&a, (void*)&b, (void*)&c }), nullptr, true);
				s->thread->join();
				std::cout << c << std::endl;
				break;
			default:
				std::cout << "def" << std::endl;
				break;
		}
	}
}