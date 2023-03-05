#pragma once
#include "Engine/memory/object.h"
#include "memory/include/stream.h"
#include "Engine/functions/function.h"

#include <Windows.h>

typedef std::vector<functionfactory::basicfunction*>* (*DLLPROC)();
struct do_win : functionfactory::function { using function::function; };
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
	static std::vector<functionfactory::basicfunction*>* dllf;// = ((DLLPROC)GetProcAddress(LoadLibrary(L"algebra.dll"), "getfunctions"))();
	static std::vector<size_t>* sizes = new std::vector<size_t>({
		sizeof(void*),	//8
		sizeof(int),	//4
		5				//5
	});
	static void* window = nullptr;
	static memory::stream::stream* s;
	static memory::stream::stream* us;
	static memory::stream::stream* controlstream = new memory::stream::stream(nullptr, 1, nullptr);	//id is VERY IMPORTANT!!!
	static std::thread* th;
	static int a = 10, b = 5, c = 0, w = 800;
	static uint64_t e = 0;
	static std::vector<void*>* args = new std::vector<void*>({ (void*)&a, (void*)&c, (void*)&c });
	static do_win do_window{
		0,	//name
		{   //defaultvalues
			&window, &w
		}
	};
	void inline inittestdata() {
		DLLPROC functogetfucns;
		std::vector<void*> vec({(void*)L"algebra.dll", &functogetfucns, 0, 0});
		memory::function::importfunction.execute(&vec, nullptr, false, nullptr);
		dllf = functogetfucns();
		HMODULE hwndm = LoadLibrary(L"HWND.dll");
		DLLPROC hwndpa = (DLLPROC)GetProcAddress(hwndm, "getfunctions");
		std::vector<functionfactory::basicfunction*>* hwndf = ((DLLPROC)GetProcAddress(LoadLibrary(L"HWND.dll"), "getfunctions"))();
		std::copy(hwndf->begin(), hwndf->end(), std::back_inserter(*dllf));
		//check function id`s
		for (functionfactory::basicfunction* bf : *dllf) {
			std::cout << bf->getid() << std::endl;
		}
		//stream
		s = new memory::stream::stream((*dllf)[0], 0, controlstream);
		us = new memory::stream::stream(&do_window, 0, controlstream);
		//window
		do_window.callings = {
			{
				(*dllf)[10],
				{
					{0, false}
				}
			},
			{
				(*dllf)[13],
				{
					{0, false},
					{1, false}
				}
			},
			{
				(*dllf)[18],
				{}
			}
		};
		us->execute(new std::vector<void*>(), nullptr, false);
		//register type`s size
		memory::table::registernewtype(1, 4);
	}
	void inline test(int testmode) {
		switch (testmode) {
			memory::object::iterator* i;
			case INITMEM:
				memory::object::memorycontroller::instance(sizes);
				for (memory::object::typeallocator* typealloc : memory::object::memorycontroller::instance()->objects) {
					std::cout << std::left << std::setw(6) << "size: ";
					std::cout << std::left << std::setw(7) << typealloc->gettypesize();
					std::cout << std::left << std::setw(8) << "length: ";
					std::cout << typealloc->getlistsize() << std::endl;
				}
				break;
			case TERMMEM:
				delete memory::object::memorycontroller::instance();
				break;
			case LOG:
				memory::object::memorycontroller::instance()->objects[1]->log_data();
				break;
			case RESIZEBIG:
				memory::object::memorycontroller::instance()->objects[1]->setlistsize(15, true);
				break;
			case RESIZESMALL:
				memory::object::memorycontroller::instance()->objects[1]->setlistsize(5, true);
				break;
			case ADD_OBJ:
				memory::object::memorycontroller::instance()->addobject(0x100000000, true, s);
				std::cout << "ADD" << std::endl;
				break;
			case OP_INT_SET_0:
				i = memory::object::memorycontroller::instance()->getobject(1, false);
				*(int*)i->getpointer() = 0;
				break;
			case OP_INT_ADD:
				i = memory::object::memorycontroller::instance()->getobject(1, false);
				*(int*)i->getpointer() = *(int*)i->getpointer() + 1;
				break;
			case LOG_INT_OBJ:
				i = memory::object::memorycontroller::instance()->getobject(1, false);
				std::cout << *(int*)i->getpointer() << std::endl;
				break;
			case THREAD_CREATE:
				s->execute(args, nullptr, true);
				s->joinstream(controlstream);
				std::cout << c << std::endl;
				break;
			case THREAD_DELETE:
				s->killstream(controlstream);
				break;
			default:
				std::cout << "def" << std::endl;
				break;
		}
	}
}