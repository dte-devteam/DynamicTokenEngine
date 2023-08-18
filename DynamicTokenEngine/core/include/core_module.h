#pragma once
#include "token/stream/include/stream.h"
#include "module/include/module_info.h"

namespace dte_core {
	//structs
	struct add_object_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::stream::stream* caller, tokenoperator::dte_token::function::bf_args* argument_pointer, bool forced = false);
	};
	struct add_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::stream::stream* caller, tokenoperator::dte_token::function::bf_args* argument_pointer, bool forced = false);
	};
	struct execute_function_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::stream::stream* caller, tokenoperator::dte_token::function::bf_args* argument_pointer, bool forced = false);
	};
	//instances
	inline tokenoperator::dte_module::module_source core_module_sources[] = {
		{ new add_object_struct			(tokenoperator::dte_token::token_name(L"add_object",		std::char_traits<wchar_t>::length(L"add_object"			))) },
		{ new add_module_struct			(tokenoperator::dte_token::token_name(L"add_module",		std::char_traits<wchar_t>::length(L"add_module"			))) },
		{ new execute_function_struct	(tokenoperator::dte_token::token_name(L"execute_function",	std::char_traits<wchar_t>::length(L"execute_function"	))) }
	};
	//module_info
	inline tokenoperator::dte_module::module_info core_module_info{L"DTE.exe"};	//(to do) is relative path appliable?
}
