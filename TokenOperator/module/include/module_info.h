#pragma once
#include "module_version.h"
#include "target_architecture.h"
#include <minwindef.h>
#include <cvt/wstring>
namespace tokenoperator::dte_module {
	struct module_info : dte_token::object {
		public:
			module_info(std::wstring dllname, uint64_t ID = 0);
			~module_info();
		protected:
			std::wstring dllname;
			HMODULE library;
			module_version version;
			void search_for_version(std::wstring& fullpath);
			void fetch_module_data();
	};
}