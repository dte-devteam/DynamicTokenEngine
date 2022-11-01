#pragma once
#include <vector>
#include <iostream>	//temp
#include <iomanip>	//temp
#include "stream.h"
using namespace std;
namespace memory {
	namespace object {
		struct iterator {
			iterator(size_t typesize);
			virtual ~iterator();
			uint64_t id = 0;
			uint64_t type = 0;
			bool isblocked = false;	//make atomic
			void* pointer;
			vector<stream::stream*> usedbystreams;
		};
		class typeallocator {
			friend class memorycontroller;
			public:
				typeallocator(size_t typesize, size_t listsize);
				virtual ~typeallocator();
				int setlistsize(size_t listsize, bool forced);
				void unregisterobject(iterator* iter, stream::stream* caller);
				iterator* addobject(uint64_t type, stream::stream* caller);
				iterator* getobject(uint64_t id, bool maywrite, stream::stream* caller);
				size_t gettypesize();
				size_t getlistsize();

				//iterator* objdesc;	//MAKE THIS PRIVATE!!!
				vector<iterator*> iters;
				//temprorary debug functions (debug should be throught basicfunctions!)
				void log_data(bool extended = false);
			private:
				size_t typesize;
				void* memoryblock;
				//iterator* objdesc;
		};
		class memorycontroller {
			public:
				static inline size_t defaultlistsize = 10;
				virtual ~memorycontroller();	//почему в итоге память не высвобождается?!
				static memorycontroller* instance(vector<size_t>* types = nullptr);
				void addtypeallocator(size_t typesize, size_t listsize = defaultlistsize);
				void deltypeallocator(size_t typesize);
				iterator* getobject(uint64_t id, bool maywrite = true, stream::stream* caller = nullptr);
				uint64_t getfreeid();
				vector<typeallocator*> objects;	//MAKE THIS PRIVATE!!!
			protected:
				memorycontroller(vector<size_t>* sizes);
			private:
				static memorycontroller* _instance;
				vector<uint64_t> potentialfreeid;
		};
	}
}