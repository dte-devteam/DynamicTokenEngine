#pragma once
#include <cvt/wstring>
#include "module_version.h"
namespace module {
	class module_requirement {
		public:
			module_requirement(std::wstring dllname, module_version minversion = MIN_MODULE_VERSION, module_version maxversion = MAX_MODULE_VERSION);
			std::wstring getname();
			module_version getminversion();
			module_version getmaxversion();
		protected:
			std::wstring dllname;
			module_version versions[2]; //min is [0], max is [1]
	};
}