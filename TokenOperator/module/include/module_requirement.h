#pragma once
#include <cvt/wstring>
#include "module_version.h"
namespace module {
	class module_requirement {
		public:
			module_requirement(std::wstring dllname, module_version minversion, bool critical = true);
			std::wstring getname();
			module_version getminversion();
			bool iscritical();
		protected:
			std::wstring dllname;
			module_version minversion;
			bool critical;
	};
}