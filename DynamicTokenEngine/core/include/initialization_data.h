#pragma once
#include "token/include/function.h"
namespace dte_core {
	bool call_dynamic_function(dte_token::func_args& stack, const size_t stack_frame_begin);




	bool add(dte_token::func_args& stack, const size_t stack_frame_begin);
}