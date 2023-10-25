#pragma once
#include "module_version.h"
namespace tokenoperator::dte_module {
	struct module_requirement : dte_token::data::value<std::array<module_version, 2>> {	//vesrions: min is [0], max is [1]
		public:
			module_requirement(std::wstring dllname, module_version minversion = module_version(), module_version maxversion = module_version(0, MAX_MODULE_VERSION), uint64_t ID = 0);
			//to do module_requirement(const module_requirement& mr);
		protected:
			std::wstring dllname;
	};
}