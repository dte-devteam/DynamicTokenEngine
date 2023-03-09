#pragma once
#include <stdint.h>
#include <thread>
#include <atomic>
#include "function/include/functionfactory.h"
#include "data/include/errorvalues.h"
namespace memory {
	namespace stream {
		class absolutestreamrights {
			public:
				absolutestreamrights(bool killstreamrights = false, bool semaphorerights = false, bool joinrights = false, bool memoryrights = false);
				bool getkillrights();
				bool getsemaphorerights();
				bool getjoinrights();
				bool getmemoryrights();
			protected:
				bool kill;
				bool semaphore;
				bool join;
				bool memoryrights;
		};
		struct createstreamstruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);	//to do
		};
		struct stream : functionfactory::basicfunction {
			public:
				stream(functionfactory::basicfunction* function, uint64_t id, stream* caller = nullptr);
				virtual ~stream();
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream = nullptr);
				void killstream(stream* caller);	//to do (придумать когда поток может быть убит), удалить поток и информацию о нем
				void joinstream(stream* caller);
				bool isalive();
				bool setfunction(functionfactory::basicfunction* func);
				uint64_t getfunctionid();

				std::vector<void*> iterators{};//private!!!
			protected:
				std::atomic_bool alive{ false };
				uint64_t* sharederrorcodepointer = nullptr;
				uint64_t* generatederrorcodepointer = new uint64_t{ 0 };
				stream* caller;
				stream* interrupterer = nullptr;
				functionfactory::basicfunction* function;
				std::thread thread = std::thread();
				absolutestreamrights* rights;
				std::vector<stream*> childstreams;
				//vector<void*> stack; (to do later, will be usefull for debug)
		};
	}
}