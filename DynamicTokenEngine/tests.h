#pragma once
#include "memory/include/object.h"
#include "memory/include/function.h"
#include "memory/include/stream.h"
using namespace memory::object;
using namespace memory::stream;
typedef std::vector<functionfactory::basicfunction*>* (*DLLPROC)();
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

		THREAD_CREATE,
		THREAD_DELETE
	};
	static std::vector<functionfactory::basicfunction*>* dllf = ((DLLPROC)GetProcAddress(LoadLibrary(L"algebra.dll"), "getfunctions"))();
	static std::vector<size_t>* sizes = new std::vector<size_t>({
		sizeof(void*),	//8
		sizeof(int),	//4
		5				//5
	});
	static stream* s = new stream((*dllf)[0], 0);
	static stream* us = new stream(nullptr, 1);
	static int a = 10, b = 5, c = 0;
	static uint64_t e = 0;
	static std::vector<void*>* args = new std::vector<void*>({ (void*)&a, (void*)&c, (void*)&c });
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
				memorycontroller::instance()->objects[0]->addobject(1, true, s);
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
				s->execute(args, nullptr, true);
				s->joinstream(us);
				std::cout << c << std::endl;
				break;
			case THREAD_DELETE:
				s->killstream(s);
				break;
			default:
				std::cout << "def" << std::endl;
				break;
		}
	}
}