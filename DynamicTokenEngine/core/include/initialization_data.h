#pragma once
#include "token/include/function.h"
namespace dte_core {
	size_t call_static_function(dte_token::long_args& stack, const size_t stack_frame_begin, const dte_token::dynamic_function::function_step& step);
	size_t call_dynamic_function(dte_token::long_args& stack, const size_t stack_frame_begin, const dte_token::dynamic_function::function_step& step);
	size_t push_link(dte_token::long_args& stack, const size_t stack_frame_begin, const dte_token::dynamic_function::function_step& step);




	bool add(dte_token::long_args& stack, const size_t stack_frame_begin);
}