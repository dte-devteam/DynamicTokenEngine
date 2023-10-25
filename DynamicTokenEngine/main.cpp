#include "tests.h"
#include "core/include/root_scope.h"
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

#include <chrono>
#include <utility>

int main(int argc, char* argv[]) {
	exec_time et;
	test();
	std::cout << argc << " : : " << (argc > 1 ? argv[1] : argv[0]) << std::endl;
	size_t i = argc;
	while (--i) {
		std::cout << i << " : : " << argv[i] << std::endl;
	}
	stream::basic_stream s(nullptr, 0);	//to do main function
	s.callstack = new std::stack<uint64_t>();
	dte_core::init_root_scope(0, 0, 0, s);
	std::cout << "root size: " << dte_core::root_scope->get_size() << std::endl;
	tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_token::object> core_pointer = (*dte_core::root_scope)[tokenoperator::dte_token::TOKEN_NAME(L"DTE_CORE")].first;
	std::cout << core_pointer.get_type().get_name() << std::endl;
	tokenoperator::dte_token::data::scope* core_scope = (tokenoperator::dte_token::data::scope*)core_pointer.get_pointer();
	std::cout << "core size: " << core_scope->get_size() << std::endl;
	tokenoperator::dte_token::function::basic_function* hi_core = (tokenoperator::dte_token::function::basic_function*)(*core_scope)[tokenoperator::dte_token::TOKEN_NAME(L"test_core")].first.get_pointer();
	tokenoperator::dte_token::function::basic_function* import_dll = (tokenoperator::dte_token::function::basic_function*)(*core_scope)[tokenoperator::dte_token::TOKEN_NAME(L"import_module")].first.get_pointer();
	tokenoperator::dte_token::function::basic_function* exec_function = (tokenoperator::dte_token::function::basic_function*)(*core_scope)[tokenoperator::dte_token::TOKEN_NAME(L"execute_function")].first.get_pointer();
	hi_core->execute(s, tokenoperator::dte_token::function::bf_args());
	std::wstring target_name = L"test_core";	//if use L"DTE_CORE/test_core" - replace core_scope in args0_source to nullptr
	tokenoperator::dte_token::data::scope_path path = tokenoperator::dte_token::data::token_path(target_name.c_str(), target_name.size());
	tokenoperator::dte_token::data::value<std::wstring> module_name(L"HWND.dll");
	tokenoperator::dte_token::object* args0_source[] = {
		core_scope,
		&path,
		&s,
		nullptr
	};
	tokenoperator::dte_token::object* args1_source[] = {
		&module_name
	};
	tokenoperator::dte_token::function::bf_args args0 (ARRAYSIZE(args0_source), args0_source);
	tokenoperator::dte_token::function::bf_args args1 (ARRAYSIZE(args1_source), args1_source);
	exec_function->execute(s, args0);
	import_dll->execute(s, args1);

	tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_token::object> hwnd_pointer = (*dte_core::root_scope)[tokenoperator::dte_token::TOKEN_NAME(L"HWND.dll")].first;
	tokenoperator::dte_token::data::scope* hwnd_scope = (tokenoperator::dte_token::data::scope*)hwnd_pointer.get_pointer();
	tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_token::object> win_obj = (*hwnd_scope)[tokenoperator::dte_token::TOKEN_NAME(L"create_win")].first;
	if (win_obj.get_pointer()) {
		std::cout << win_obj.get_type().get_name() << std::endl;
		((tokenoperator::dte_token::function::basic_function*)win_obj.get_pointer())->execute(s, args0);
	}

	std::cout << "dt: " << et.get_dt() << std::endl;
	//#ifndef _DEBUG //for .exe launch directly
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	//#endif
	return 0;
}