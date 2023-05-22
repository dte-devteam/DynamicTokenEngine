#pragma once
#include "token/function/include/basicfunction.h"
namespace tokenoperator::token::stream {
	struct stream : function::basicfunction {
		public:
			stream(uint64_t ID = 0, function::basicfunction* function = nullptr);
			void execute(function::args* argumentspointer, uint64_t* errorcodepointer, bool forced, function::stack* callstack = nullptr, stream* caller = nullptr);
			uint64_t getfunctionID() const;
		protected:
			function::basicfunction* function;
	};
}