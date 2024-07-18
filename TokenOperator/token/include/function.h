#pragma once
#include "utils/include/pointer.h"
#include "token.h"
namespace dte_token {
	typedef dte_utils::dynamic_array<token::link> long_args;
	typedef bool (*function)(long_args);	//long_args&& with std::move?
	struct function_call {
		virtual bool execute(long_args) = 0;
	};
	struct function_info {
		//to do info
	};
	struct funtion_literal : function_call {
		//to do
		bool execute(long_args args);
	};
	struct dll_function : function_info, function_call {
		function fp;
		bool execute(long_args args);
	};
	struct dynamic_function : function_info, function_call {
		struct function_step {
			size_t jump;
			dte_utils::weak_ref<function_call> fc;
		};
		dte_utils::dynamic_array<function_step> functions;
		//to do literal storage
		bool execute(long_args args);
	};
}