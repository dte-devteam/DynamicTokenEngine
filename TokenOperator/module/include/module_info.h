#pragma once
#include "module_source.h"
#include "module_version.h"
#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>
#include <libloaderapi.h>
namespace tokenoperator::dte_module {
	struct module_info : dte_token::data::value<std::pair<module_source*, size_t>> {
		public:
			module_info(std::wstring dllname, uint64_t ID = 0);
			module_info(const module_info& mi);
			~module_info();
			std::wstring get_dllname();
		protected:
			std::wstring dllname;
			HMODULE library;
			module_version version;
			void search_for_version(std::wstring& fullpath);
	};
}