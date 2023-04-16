#pragma once
#include <stdint.h>
#include <thread>
#include <atomic>
#include "function/include/basicfunction.h"
#include "data/include/errorvalues.h"
#include "absolutestreamrights.h"
namespace stream {
	struct stream : function::basicfunction {
		public:
			stream(basicfunction* function, uint64_t id, stream* caller = nullptr);
			virtual ~stream();
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream = nullptr);
			bool killstream(stream* caller);	//to do (придумать когда поток может быть убит), удалить поток и информацию о нем
			void joinstream(stream* caller);
			bool isalive();
			bool setfunction(basicfunction* func);
			uint64_t getfunctionid();

			std::vector<void*> iterators{};//private!!!
			bool maywrite = false;//private!!!
		protected:
			std::atomic_bool alive{ false };
			uint64_t* sharederrorcodepointer = nullptr;
			uint64_t* generatederrorcodepointer = new uint64_t{ 0 };
			stream* caller;
			stream* interrupterer = nullptr;
			basicfunction* function;
			std::thread thread = std::thread();
			absolutestreamrights* rights;
			std::vector<stream*> childstreams;
			//vector<void*> stack; (to do later, will be usefull for debug)
	};
}