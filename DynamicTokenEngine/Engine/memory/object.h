#pragma once
#include <vector>
#include <mutex>
#include <iostream>	//temp
#include <iomanip>	//temp
#include "stream/include/stream.h"
#include "module/include/typedesc.h"
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

//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
//полностью - любая вставленная модификация может привести полному краху, без возможности узнать источник ошибки
namespace memory {
	namespace object {
		class iterator {
			//think of atomic or mutex
			friend class memorycontroller;
			public:
				iterator();
				virtual ~iterator();
				std::vector<stream::stream*> usedbystreams;
				void* getpointer(stream::stream* caller);
				uint64_t getid();
				uint64_t gettype();
				uint32_t getsupertype();
				uint32_t getflags();
				void settype(stream::stream* caller, module::typedesc* typeinstance);
				void setflags(stream::stream* caller, uint32_t flags);
				void unregisterobject(stream::stream* caller);
			private:
				iterator(stream::stream* caller, module::typedesc* typeinstance, uint64_t id, uint32_t flags, bool iscriticalsection);
				/*
				* чтобы не запутаться:
				* blocker это первый (по приоритету), кто может писать
				* iscriticalsection это сигнал о том, что только blocker или поток с maywrite = false может получит доступ к объекту
				*/
				stream::stream* blocker = nullptr;
				module::typedesc* typeinstance = nullptr;
				uint64_t id = 0;
				uint32_t flags = 0;
				void* pointer = nullptr;
				bool iscriticalsection = false;
				void create_value(module::typedesc* typeinstance);
				void kill_value();
		};
		class memorycontroller {
			public:
				static inline size_t defaultlistsize = 10;
				virtual ~memorycontroller();	//почему в итоге память не высвобождается?!
				static memorycontroller* instance();
				static memorycontroller* instance(std::vector<std::pair<module::typedesc*, size_t>> initstartmemory);
				iterator* addobject(module::typedesc* typeinstance, uint32_t flags = 0, stream::stream* caller = nullptr, bool getascritical = false);	//add stream safe (critical section or smth)
				iterator* getobject(uint64_t id, size_t size = 0, stream::stream* caller = nullptr, bool getascritical = false);
				void setlistsize(size_t listsize, bool forced = false, size_t datasize = 0);
				std::vector<std::pair<size_t, std::vector<iterator>>> objects;	//MAKE THIS PRIVATE!!!

				//logs
				void log_size(bool extended = false, size_t size = 0);
				void log_iterator(iterator& i, size_t shift, bool extended = false);
			protected:
				memorycontroller(std::vector<std::pair<module::typedesc*, size_t>>* initstartmemory = nullptr);
			private:
				static memorycontroller* _instance;
				uint64_t getfreeid();
				std::mutex mutex;
		};
	}
}