#pragma once
#include "target_architecture.h"
#include <minwindef.h>
#include "data_desc.h"
#include "dependency_desc.h"
namespace module_desc {
	typedef std::vector<dependency_desc::function_data>* (*DLL_PROC_FD)();
	typedef std::vector<data_desc::typedesc>* (*DLL_PROC_T)();
	typedef std::vector<data_desc::valuedesc*>* (*DLL_PROC_V)();
	typedef std::vector<dependency_desc::module_requirement>* (*DLL_PROC_MR)();
	class module {
		public:
			module(std::wstring dllname = std::wstring());
			virtual ~module();
			std::wstring getdllname();
			HMODULE getlibrary();
			std::vector<dependency_desc::function_data>* functions;
			std::vector<data_desc::typedesc>* types;
			std::vector<data_desc::valuedesc*>* data;
			std::vector<dependency_desc::module_requirement>* requirements;
			dependency_desc::module_version getversion();
		protected:
			std::wstring dllname;
			HMODULE library;
			dependency_desc::module_version version;
		private:
			void search_for_version(std::wstring dllname);
			void fetch_module_data();
	};
}