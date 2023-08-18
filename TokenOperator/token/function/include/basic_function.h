#pragma once
#include "bf_args.h"
#include "../error_codes.h"
#include <stack>
//stack defines
#define ENTER_STACK caller->callstack->push(ID);
#define EXIT_STACK  if (caller->errorcode) { return; } caller->callstack->pop();
//raising error defines
#define RAISE_ERROR(error) caller->errorcode = error; return;
#define REQUIRE_ARGS_CUSTOM(error) if (!argument_pointer) { RAISE_ERROR(error) }; if (!argument_pointer->get_data()) { RAISE_ERROR(error) }
#define REQUIRE_ARGS REQUIRE_ARGS_CUSTOM(DTE_EC_DATA_NULLPTR)
#define REQUIRE_ARG_NUM(min_arg_num) if (argument_pointer->get_size() < min_arg_num) { RAISE_ERROR(DTE_EC_LOW_ARG_NUM) }
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
		* 
		* for function input it`s better to create notes of bf_args types:
		* [n] - some type
		*/
		struct basic_function : object {
			public:
				basic_function(uint64_t ID = 0, bf_args defaultvalues = {0, nullptr});
				virtual void execute(stream::stream* caller, bf_args* argument_pointer,  bool forced = false) = 0;
			protected:
				bf_args defaultvalues;
		};
	}
}