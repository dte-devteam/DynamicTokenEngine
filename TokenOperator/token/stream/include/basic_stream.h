#pragma once
#include "token/function/include/basic_function.h"
#include "token/data/include/smart_pointer.h"
#include <thread>
#include <atomic>
#include <stack>
namespace tokenoperator::dte_token::stream {
	struct basic_stream : function::basic_function {
		friend struct stream_data;
		public:
			basic_stream(data::smart_pointer<object> function, uint64_t ID = 0);
			~basic_stream();
			void execute(const basic_stream& caller, const function::bf_args& argument_pointer, bool forced = false);
			uint64_t getfunctionID() const;
			void killstream();
			void joinstream();
			bool isalive();
			//make below protected later (to do)
			data::smart_pointer<std::stack<uint64_t>> callstack;
			uint64_t errorcode;
		protected:
			data::smart_pointer<object> function;
			std::thread thread;
			std::atomic_bool alive;
			void free_stream_data();
			//to do thread requested data (smart_pointer<object>)
	};
}