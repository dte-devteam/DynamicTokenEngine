#pragma once
#include "target_architecture.h"
#include <minwindef.h>
#include "typedesc.h"
#include "module_requirement.h"

#include "export_data.h"
namespace module {
	typedef std::vector<function_data> DTE_MODULE_FD; //typedef std::vector<function_data>* DTE_MODULE_FD;
	typedef std::vector<typedesc> DTE_MODULE_TD;
	typedef std::vector<value_data> DTE_MODULE_VD;
	typedef std::vector<module_requirement> DTE_MODULE_MR;
	class module {
		public:
			module(std::wstring dllname = L"", std::wstring path = L"");
			module(const module& parent);
			virtual ~module();
			std::wstring getdllname() const;
			HMODULE getlibrary();
			DTE_MODULE_FD* functions;
			DTE_MODULE_TD* types;
			DTE_MODULE_VD* data;
			DTE_MODULE_MR* requirements;
			module_version getversion();
			bool operator ==(module& module_instance);
			bool operator ==(module&& module_instance);
		protected:
			std::wstring dllname;
			HMODULE library;
			module_version version;
		private:
			void search_for_version(std::wstring& fullpath);
			void fetch_module_data();
	};
}