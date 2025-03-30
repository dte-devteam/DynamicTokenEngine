#pragma once
#include <iostream>
#include "function_stack.h"
#include "token.h"

import utils.pointer.weak_ref;
import utils.pointer.strong_ref;

import utils.dynamic_memory.dynamic_array;
namespace dte_token {
	typedef bool (*cfunc)(function_stack& stack, const size_t frame_offset);
	struct dynamic_function {
		struct step {
			size_t block_offset;
			size_t jump_index;
			dte_utils::strong_ref<token> literal;
			dte_utils::weak_ref<cfunc> f;
		};
		dte_utils::dynamic_array<step> steps;
		bool execute(function_stack& stack, const size_t frame_offset);
	};
}