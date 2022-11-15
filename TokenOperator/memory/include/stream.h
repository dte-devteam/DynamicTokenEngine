#pragma once
#include <stdint.h>
#include <thread>
#include <semaphore>
#include "../../function/include/functionfactory.h"
#include "metatable.h"
using namespace functionfactory;
namespace memory {
	namespace stream {
		class absolutestreamrights {
			public:
				bool getkillrights();
				bool getsemaphorerights();
			private:
				bool killstream;
				bool semaphore;
		};
		struct createstreamstruct : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);	//to do
		};
		struct stream : basicfunction {
			public:
				stream(basicfunction* function, uint64_t id, stream* caller);
				void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
				//void execute(){}	//add function arguments
				void interrupt(stream* caller) {}	//to do, interrupterid нельзя заменить, если он не 0!
				void proceed(stream* caller) {}	//to do, если id совпадает, возобновляем работу
				void killstream(stream* caller, bool shouldjoin);	//to do (придумать когда поток может быть убит), удалить поток и информацию о нем
				bool isalive();
				bool iswaiting();
				std::thread* thread = nullptr;
			protected:
				~stream();
			private:
				stream* caller;
				stream* interrupterer = 0;
				basicfunction* function;
				//std::thread thread;
				std::binary_semaphore semaphore{0};
				//vector<void*> stack;
				std::vector<stream*> childstreams;
				absolutestreamrights* rights;
		};
		//static vector<stream*> treads;
	}
}