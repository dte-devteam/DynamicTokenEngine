#pragma once
#include "token/object.h"
#include <vector>
namespace tokenoperator::dte_token {
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
		using args = std::vector<object*>;
		using stack = std::vector<basic_function*>;
		struct basic_function : object {
			public:
				basic_function(uint64_t ID = 0, args defaultvalues = {});
				virtual void execute(args* argumentspointer, uint64_t* errorcodepointer = nullptr, bool forced = false, stack* callstack = nullptr, stream::stream* caller = nullptr) = 0;
			protected:
				args defaultvalues;
				void form_argument(args* argumentspointer, args& target) const;
		};
	}
}