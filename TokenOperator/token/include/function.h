#pragma once
#include "utils/include/pointer.h"
#include "token.h"
namespace dte_token {
	typedef dte_utils::dynamic_array<dte_utils::strong_ref<token, false>> func_args;
	typedef bool (*function)(func_args&, const size_t);
	size_t get_function_frame_size(func_args& stack, const size_t stack_frame_begin);
	void clear_function_frame(func_args& stack, const size_t stack_frame_begin);
	struct dynamic_function {
		struct function_step {
			size_t								frame_offset;
			size_t								index;		//if function - jump, else - index of data in stack
			dte_utils::weak_ref<function>		func;
			dte_utils::strong_ref<token, false> literal;
		};
		public:
			dte_utils::dynamic_array<function_step> steps;
			void execute(func_args& stack, const size_t stack_frame_begin = 0) const;
	};
	/*
	typedef size_t (*step_action)(func_args&, const size_t, const dynamic_function::function_step&);// to do
	struct dynamic_function::function_step {
		struct value_action {
			dte_utils::dynamic_wstring search_name;
			dte_utils::strong_ref<token, false> literal;
		};
		struct function_action {
			dte_utils::weak_ref<function> func;
			size_t jump;
			size_t overlap;
		};
		value_action						va;
		function_action						fa;
		dte_utils::weak_ref<step_action>	action;
	};
	*/
}