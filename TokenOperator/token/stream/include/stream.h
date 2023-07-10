#pragma once
#include "token/function/include/basic_function.h"
#include "token/data/include/smart_pointer.h"
namespace tokenoperator::dte_token::stream {
	struct stream : function::basic_function {
		public:
			stream(data::smart_pointer<function::basic_function> function, uint64_t ID = 0);
			void execute(function::args* argumentspointer, uint64_t* errorcodepointer, bool forced, function::stack* callstack = nullptr, stream* caller = nullptr);
			uint64_t getfunctionID() const;
		protected:
			data::smart_pointer<function::basic_function> function;
			//to do thread requested data (smart_pointer<object>)
	};
}