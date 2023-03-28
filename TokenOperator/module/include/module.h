#pragma once
#include "target_architecture.h"
#include <minwindef.h>
#include "typedesc.h"
#include "valuedesc.h"
#include "module_requirement.h"
#include "function_data.h"
namespace module {
	typedef std::vector<function_data>* (*DLL_PROC_FD)();
	typedef std::vector<typedesc>* (*DLL_PROC_TD)();
	typedef std::vector<valuedesc*>* (*DLL_PROC_VD)();
	typedef std::vector<module_requirement>* (*DLL_PROC_MR)();
	class module {
		public:
			module(std::wstring dllname = std::wstring());
			virtual ~module();
			std::wstring getdllname();
			HMODULE getlibrary();
			std::vector<function_data>* functions;
			std::vector<typedesc>* types;
			std::vector<valuedesc*>* data;
			std::vector<module_requirement>* requirements;
			module_version getversion();
		protected:
			std::wstring dllname;
			HMODULE library;
			module_version version;
		private:
			void search_for_version(std::wstring dllname);
			void fetch_module_data();
	};
}