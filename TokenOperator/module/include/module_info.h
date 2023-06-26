#pragma once
#include "token/data/include/scope.h"
#include "module_version.h"
#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>
#include <libloaderapi.h>
namespace tokenoperator::dte_module {
	struct module_info : dte_token::object {
		public:
			module_info(std::wstring dllname, uint64_t ID = 0);
			~module_info();
		protected:
			std::wstring dllname;
			HMODULE library;
			module_version version;
			dte_token::data::smart_pointer<object> module_scope;
			void search_for_version(std::wstring& fullpath);
	};
}