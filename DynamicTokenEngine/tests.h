#pragma once
#include "Engine/memory/object.h"
#include "stream/include/stream.h"
#include "Engine/functions/function.h"

#include <Windows.h>



//#include "module/include/data_desc.h"
#include "module/include/module.h"
typedef std::vector<function::basicfunction*>* (*DLLPROC)();
struct do_win : function::function { using function::function; };
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
	static std::vector<module::module> modules;
	static std::vector<function::basicfunction*>* dllf;// = ((DLLPROC)GetProcAddress(LoadLibrary(L"algebra.dll"), "getfunctions"))();
	static std::vector<std::pair<module::typedesc*, size_t>> types = { //sizes
		{	//int*
			new module::typedesc(token_data::token_type_to_id(L"int"), sizeof(int)),
			0
		},
		{	//void*
			new module::typedesc(token_data::token_type_to_id(L"void*"), sizeof(void*)),
			0
		},
		{	//type5
			new module::typedesc(token_data::token_type_to_id(L"type5"), 5),
			0
		}
	};
	static std::vector<void*> nodata;
	static void* window = nullptr;
	static stream::stream* s;
	static stream::stream* us;
	static stream::stream* controlstream = new stream::stream(nullptr, 1, nullptr);	//id is VERY IMPORTANT!!!
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
		modules.push_back({ L"algebra.dll" });
		modules.push_back({ L"HWND.dll" });
		//for (module_desc::module& m : modules) {
		//	std::wcout << m.getdllname() << std::endl;
		//	if (m.functions) {
		//		for (dependency_desc::function_data& fd : *m.functions) {
		//			std::cout << fd.function->getid() << std::endl;
		//		}
		//	}
		//}
		//std::cout << "--------------" << std::endl;



		DLLPROC functogetfucns;
		std::vector<void*> vec({(void*)L"algebra.dll", &functogetfucns, 0, 0});
		memory::importfunction.execute(&vec, nullptr, false, nullptr);
		dllf = functogetfucns();
		HMODULE hwndm = LoadLibrary(L"HWND.dll");
		DLLPROC hwndpa = (DLLPROC)GetProcAddress(hwndm, "getfunctions");
		std::vector<function::basicfunction*>* hwndf = hwndpa();
		std::copy(hwndf->begin(), hwndf->end(), std::back_inserter(*dllf));
		//check function id`s
		//for (functionfactory::basicfunction* bf : *dllf) {
		//	std::cout << bf->getid() << std::endl;
		//}
		//stream
		s = new stream::stream((*modules[0].functions)[0].function, 0, controlstream);
		us = new stream::stream(&do_window, 0, controlstream);
		s->maywrite = false;
		us->maywrite = false;
		//window
		do_window.callings = {
			{
				(*dllf)[10],
				//(*modules[1].functions)[1].function,	//10 - error
				{
					{0, false}
				}
			},
			{
				(*dllf)[13], 
				//(*modules[1].functions)[4].function,	//13
				{
					{0, false},
					{1, false}
				}
			},
			{
				(*dllf)[18], 
				//(*modules[1].functions)[9].function,	//18
				{}
			}
		};
		std::vector<void*>* fargs = new std::vector<void*>({ &window });
		delete fargs;
		us->execute(&nodata, nullptr, false);
	}
	void inline test(int testmode) {
		switch (testmode) {
			memory::object::iterator* i;
			case INITMEM:
				//std::cout << "INIT" << std::endl;
				memory::object::memorycontroller::instance(types);
				break;
			case TERMMEM:
				delete memory::object::memorycontroller::instance();
				break;
			case LOG:
				memory::object::memorycontroller::instance()->log_size();
				break;
			case RESIZEBIG:
				//std::cout << "BIG" << std::endl;
				memory::object::memorycontroller::instance()->setlistsize(15, true);
				break;
			case RESIZESMALL:
				//std::cout << "SMALL" << std::endl;
				memory::object::memorycontroller::instance()->setlistsize(5, true);
				break;
			case ADD_OBJ:
				//std::cout << "ADD" << std::endl;
				memory::object::memorycontroller::instance()->addobject(types[0].first, 0, s, false);
				break;
			case OP_INT_SET_0:
				i = memory::object::memorycontroller::instance()->getobject(1, 4);
				*(int*)i->getpointer(s) = 0;
				break;
			case OP_INT_ADD:
				i = memory::object::memorycontroller::instance()->getobject(1, 4);
				*(int*)i->getpointer(s) = *(int*)i->getpointer(s) + 1;
				break;
			case LOG_INT_OBJ:
				i = memory::object::memorycontroller::instance()->getobject(1, 4);
				std::cout << *(int*)i->getpointer(s) << std::endl;
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