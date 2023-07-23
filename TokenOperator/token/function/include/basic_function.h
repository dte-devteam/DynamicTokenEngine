#pragma once
#include "bf_args.h"
#include <vector>
namespace tokenoperator::dte_token {
	#define USE_STACK if (callstack) { callstack->push_back(ID); }
	namespace stream {
		struct stream;
	}
	namespace function {
		/*
		* for debug purpose you can add to stack executing function:
		* if (callstack) callstack->push_back(this);
		* some_code_to_exec();
		* if (callstack) callstack->pop_back();
		*
		* it`s recomended for any function
		*/
		struct basic_function;
		using stack = std::vector<uint64_t>;
		struct basic_function : object {
			public:
				basic_function(uint64_t ID = 0, bf_args defaultvalues = {0, nullptr});
				inline virtual void execute(bf_args* argumentspointer, uint64_t* errorcodepointer = nullptr, bool forced = false, stack* callstack = nullptr, stream::stream* caller = nullptr) = 0;
			protected:
				bf_args defaultvalues;
				bf_args form_argument(bf_args* argumentspointer) const;
		};
	}
}