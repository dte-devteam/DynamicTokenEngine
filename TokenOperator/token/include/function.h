#pragma once
#include "utils/include/pointer.h"
#include "token.h"
namespace dte_token {
	typedef dte_utils::dynamic_array<token::link> long_args;
	typedef bool (*function)(long_args&, const size_t);
	__forceinline void clear_function_frame(long_args& stack, const size_t stack_frame_begin);
	struct dynamic_function {
		struct function_step {
			size_t jump;
			dte_utils::weak_ref<function> fc;
			//to do literal storage
		};
		size_t stack_frame_size;
		dte_utils::dynamic_array<function_step> functions;
		void execute(long_args& stack, const size_t stack_frame_begin = 0) const;
	};
}