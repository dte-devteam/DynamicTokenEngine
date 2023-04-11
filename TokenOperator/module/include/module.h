#pragma once
#include "target_architecture.h"
#include <minwindef.h>
#include "typedesc.h"
#include "valuedesc.h"
#include "module_requirement.h"
#include "function_data.h"
namespace module {
	typedef std::vector<function_data>* DTE_MODULE_FD;
	typedef std::vector<typedesc>* DTE_MODULE_TD;
	typedef std::vector<valuedesc*>* DTE_MODULE_VD;
	typedef std::vector<module_requirement>* DTE_MODULE_MR;
	class module {
		public:
			module(std::wstring dllname = std::wstring());
			module(const module& parent);
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