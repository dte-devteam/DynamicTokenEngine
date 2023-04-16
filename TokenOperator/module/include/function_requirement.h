#pragma once
#include <cvt/wstring>
#include "desc_type.h"
#include "module_version.h"
#include "function/include/basicfunction.h"
namespace module {
	class function_requirement {
		public:
			function_requirement(uint64_t name, size_t index, desc_type desc_type);
			uint64_t getname();
			size_t getindex();
			desc_type getdesctype();
		protected:
			uint64_t name;
			size_t index;
			desc_type type;
	};
}