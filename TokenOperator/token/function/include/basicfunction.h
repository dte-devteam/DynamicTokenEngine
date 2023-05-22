#pragma once
#include "token/object.h"
#include <vector>
namespace tokenoperator::token {
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
		struct basicfunction;
		using args = std::vector<object*>;
		using stack = std::vector<basicfunction*>;
		struct basicfunction : object {
			public:
				basicfunction(uint64_t ID = 0, args _defaultvalues = {});
				virtual void execute(args* argumentspointer, uint64_t* errorcodepointer, bool forced, stack* callstack = nullptr, stream::stream* caller = nullptr) = 0;
			protected:
				args defaultvalues;
				void formargument(args* argumentspointer, args& target);
		};
	}
}