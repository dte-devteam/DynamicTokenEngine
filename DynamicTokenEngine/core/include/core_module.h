#pragma once
#include "token/stream/include/stream.h"
#include "module/include/module_info.h"
#include "token/object.h"
namespace dte_core {
	//structs
	struct add_module_object_struct : tokenoperator::dte_token::function::basic_function {
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
	struct test_core_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::stream::stream* caller, tokenoperator::dte_token::function::bf_args* argument_pointer, bool forced = false);
	};
	//instances
	inline tokenoperator::dte_token::data::scope_path dte_core_path = tokenoperator::dte_token::data::token_path(L"DTE_CORE", std::wcslen(L"DTE_CORE"), 0);
	inline tokenoperator::dte_module::module_source core_module_sources[] = {
		{{new add_module_object_struct	(tokenoperator::dte_token::TOKEN_NAME(L"add_module_object"	)), false}, nullptr, 0},
		{{new add_module_struct			(tokenoperator::dte_token::TOKEN_NAME(L"add_module"			)), false}, nullptr, 0},
		{{new execute_function_struct	(tokenoperator::dte_token::TOKEN_NAME(L"execute_function"	)), false}, nullptr, 0},
		{{new test_core_struct			(tokenoperator::dte_token::TOKEN_NAME(L"test_core"			)), false}, nullptr, 0}
	};
	//module_info
	inline tokenoperator::dte_module::module_info core_module_info{L"DTE.exe"};	//(to do) is relative path appliable?
}
