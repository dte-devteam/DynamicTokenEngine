#pragma once
#include <vector>
#include <mutex>
#include <iostream>	//temp
#include <iomanip>	//temp
#include "stream.h"
#include "metatable.h"
//to do: stream defines if it can write (+basicfunction)
/*
* memory organisation:
* memorycontroller
* |
* +-- typeallocator
*	  |
*	  +-- iterator
*		  |
*		  +-- memory object (void*)
* 
* memory usage:
* addobject - register object for usage (also getobject after creation) 
* getobject - get access to object
* unregisterobject - unregister object (memory isn`t used anymore by stream)
* 
* problems:
* heap memory defragmentation
* unable to hold class pointer safely:
*	class* turned into void*
*	thread MUST kill all created classes before death, but termination can prevent it - memory leak
* unable to hold class with dynamic size
*/
namespace memory {
	namespace object {
		class iterator {
			//think of atomic or mutex
			friend class typeallocator;
			//friend uint64_t memorycontroller::getfreeid(void);	//error C2653 why???
			public:
				iterator(size_t typesize);
				virtual ~iterator();
				std::vector<stream::stream*> usedbystreams;
				void* getpointer();
				uint64_t getid();
				uint64_t gettype();
				void settype(stream::stream* caller, uint64_t newtype);
				void setdeleter(stream::stream* caller, void (*deleter)(void*));
				void unregisterobject(stream::stream* caller);
			private:
				stream::stream* blocker = nullptr;
				void (*deleter)(void*) = nullptr;
				uint64_t id = 0;
				uint64_t type = 0;
				void* pointer;
				bool iscriticalsection = false;
		};
		class typeallocator {
			friend class memorycontroller;
			public:
				typeallocator(size_t typesize, size_t listsize);
				virtual ~typeallocator();
				int setlistsize(size_t listsize, bool forced);
				static void unregisterobject(iterator* iter, stream::stream* caller);
				iterator* addobject(uint64_t type, bool maywrite, stream::stream* caller, uint64_t id = 20, bool iscriticalsection = false);	//temp should be 0
				iterator* getobject(uint64_t id, bool maywrite, stream::stream* caller);
				size_t gettypesize();
				size_t getlistsize();

				std::vector<iterator*> iters;	//make it private!!!
				//temprorary debug functions (debug should be throught basicfunctions!)
				void log_data(bool extended = false);
			private:
				size_t typesize;
		};
		class memorycontroller {
			public:
				static inline size_t defaultlistsize = 10;
				virtual ~memorycontroller();	//почему в итоге память не высвобождается?!
				static memorycontroller* instance(std::vector<size_t>* types = nullptr);
				void addtypeallocator(size_t typesize, size_t listsize = defaultlistsize);
				void deltypeallocator(size_t typesize);
				iterator* addobject(uint64_t type, bool maywrite, stream::stream* caller = nullptr, size_t size = 0);	//add stream safe (critical section or smth)
				iterator* getobject(uint64_t id, bool maywrite = true, stream::stream* caller = nullptr);
				std::vector<typeallocator*> objects;	//MAKE THIS PRIVATE!!!
			protected:
				memorycontroller(std::vector<size_t>* sizes);
			private:
				static memorycontroller* _instance;
				uint64_t getfreeid();
				std::mutex mutex;
		};
	}
}