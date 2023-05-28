#pragma once
#include "token/function/include/basic_function.h"
namespace tokenoperator::dte_token::stream {
	struct stream : function::basic_function {
		public:
			stream(uint64_t ID = 0, function::basic_function* function = nullptr);
			void execute(function::args* argumentspointer, uint64_t* errorcodepointer, bool forced, function::stack* callstack = nullptr, stream* caller = nullptr);
			uint64_t getfunctionID() const;
		protected:
			function::basic_function* function;
	};
}