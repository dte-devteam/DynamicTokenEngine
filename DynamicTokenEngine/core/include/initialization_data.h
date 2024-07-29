#pragma once
#include "token/include/function.h"
namespace dte_core {
	inline bool call_dynamic_function(dte_token::long_args& stack, const size_t stack_frame_begin);
	inline bool set_rvalue(dte_token::long_args& stack, const size_t stack_frame_begin);
	inline bool set_lvalue(dte_token::long_args& stack, const size_t stack_frame_begin);
	inline bool clear_value(dte_token::long_args& stack, const size_t stack_frame_begin);
}