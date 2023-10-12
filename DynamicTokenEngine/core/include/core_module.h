#pragma once
#include "token/data/include/scope.h"
#include "token/stream/include/basic_stream.h"
#include "module/include/module_info.h"
#include "token/object.h"
namespace dte_core {
	//structs
	struct use_scope_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	struct add_module_object_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	struct add_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	struct import_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	struct init_module_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false) {}	//temp, to do
	};
	struct execute_function_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	//to do - read dte file
	struct read_dte_file_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	struct test_core_struct : tokenoperator::dte_token::function::basic_function {
		using tokenoperator::dte_token::function::basic_function::basic_function;
		void execute(const tokenoperator::dte_token::stream::basic_stream& caller, const tokenoperator::dte_token::function::bf_args& args, bool forced = false);
	};
	//instances
	inline tokenoperator::dte_token::data::scope_path dte_core_path = tokenoperator::dte_token::data::token_path(L"DTE_CORE", std::wcslen(L"DTE_CORE"), 0);
	inline tokenoperator::dte_module::module_source core_module_sources[] = {
		{new use_scope_struct						(tokenoperator::dte_token::TOKEN_NAME(L"use_scope"			))},
		{new add_module_object_struct				(tokenoperator::dte_token::TOKEN_NAME(L"add_module_object"	))},
		{new add_module_struct						(tokenoperator::dte_token::TOKEN_NAME(L"add_module"			))},
		{new import_module_struct					(tokenoperator::dte_token::TOKEN_NAME(L"import_module"		))},
		{new init_module_struct						(tokenoperator::dte_token::TOKEN_NAME(L"init_module"		))},
		{new execute_function_struct				(tokenoperator::dte_token::TOKEN_NAME(L"execute_function"	))},
		{new tokenoperator::dte_token::data::scope	(1, 1, tokenoperator::dte_token::TOKEN_NAME(L"modules_info"	))},
		{new test_core_struct						(tokenoperator::dte_token::TOKEN_NAME(L"test_core"			))}
	};
	//module_info
	inline tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_module::module_info> core_module_info = new tokenoperator::dte_module::module_info(L"DTE_CORE");	//(to do) is relative path appliable?
}
