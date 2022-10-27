#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>	//temp
#include <iomanip>	//temp
#include "thread.h"
using namespace std;
namespace memory {
	namespace object {
		struct iterator {
			uint64_t id = 0;
			uint64_t type = 0;
			bool isblocked = false;	//make atomic
			void* pointer = 0;
			vector<stream::stream*> usedbystreams;
		};
		static const uint64_t typemask = 0xFFFFFFFF00000000;
		class typeallocator {
			friend class memorycontroller;
			public:
				typeallocator(size_t typesize, size_t listsize);
				virtual ~typeallocator();
				int setlistsize(size_t listsize, bool forced);
				void unregisterobject(iterator* iter);
				iterator* addobject(uint64_t id, uint64_t type, stream::stream* caller);
				iterator* getobject(uint64_t id, bool maywrite, stream::stream* caller);
				size_t gettypesize();
				size_t getlistsize();

				iterator* objdesc;	//MAKE THIS PRIVATE!!!

				//temprorary debug functions (debug should be throught basicfunctions!)
				void log_data();
			private:
				size_t typesize;
				size_t listsize;
				void* memoryblock;
				//iterator* objdesc;
				vector<uint32_t> generaltypes;
				void addgeneraltype(uint64_t type);
				void delgeneraltype(uint64_t type);
				uint32_t typemasker(uint64_t type);
		};
		class memorycontroller {
			public:
				size_t defaultlistsize = 100;
				virtual ~memorycontroller();
				static memorycontroller* instance(vector<size_t>* types = nullptr);
				void addtypeallocator(size_t typesize, size_t listsize = instance()->defaultlistsize);
				void deltypeallocator(size_t typesize);
				iterator* getobject(uint64_t id, bool maywrite = true, stream::stream* caller = nullptr);
				vector<typeallocator*> objects;	//MAKE THIS PRIVATE!!!
			private:
				memorycontroller(vector<size_t>* sizes);
				static memorycontroller* _instance;
		};
	}
}