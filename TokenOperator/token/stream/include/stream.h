#pragma once
#include "token/function/error_codes.h"
#include "token/function/include/basic_function.h"
#include "token/data/include/smart_pointer.h"
#include <thread>
#include <atomic>
namespace tokenoperator::dte_token::stream {
	struct stream : function::basic_function {
		public:
			stream(data::smart_pointer<object> function, uint64_t ID = 0);
			~stream();
			void execute(function::bf_args* argumentspointer, uint64_t* errorcodepointer = nullptr, bool forced = false, function::stack* callstack = nullptr, stream* caller = nullptr);
			uint64_t getfunctionID() const;
			void killstream();
			void joinstream();
			bool isalive();
		protected:
			data::smart_pointer<object> function;
			std::thread thread;
			std::atomic_bool alive;
			uint64_t generatederrorcode;
			uint64_t* stream_errorcodepointer;
			void free_stream_data();
			//to do thread requested data (smart_pointer<object>)
	};
}