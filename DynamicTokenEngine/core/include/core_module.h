#pragma once
#include "token/function/include/basic_function.h"
#include "module/include/module_info.h"
namespace dte_core {
	//structs
	struct add_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::function::bf_args* argumentspointer, uint64_t* errorcodepointer = nullptr, bool forced = false, tokenoperator::dte_token::function::stack* callstack = nullptr, tokenoperator::dte_token::stream::stream* caller = nullptr);	//to do if only in .cpp file definition, error LNK2001
	};
	struct remove_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(tokenoperator::dte_token::function::bf_args* argumentspointer, uint64_t* errorcodepointer = nullptr, bool forced = false, tokenoperator::dte_token::function::stack* callstack = nullptr, tokenoperator::dte_token::stream::stream* caller = nullptr);	//to do if only in .cpp file definition, error LNK2001
	};

	//to do
	//execute stream

	//instances
	inline tokenoperator::dte_module::module_source core_module_sources[] = {
		new tokenoperator::dte_module::module_source(new add_module_struct		(	tokenoperator::dte_token::token_name(L"add_module",		10))),
		new tokenoperator::dte_module::module_source(new remove_module_struct	(	tokenoperator::dte_token::token_name(L"remove_module",	13)))
	};

	//module_info
	inline tokenoperator::dte_module::module_info core_module_info{L"DTE.exe"};	//(to do) is relative path appliable?
}