#pragma once
#include "token/object.h"
#include "module_version.h"
#include "target_architecture.h"
#include <minwindef.h>
#include <cvt/wstring>
namespace tokenoperator::dte_module {
	struct module_info : dte_token::object {
		public:
			//module_info();
		protected:
			//std::wstring dllname;
			HMODULE library;
			module_version version;
			void search_for_version(std::wstring& fullpath);
			//void fetch_module_data();
	};
}