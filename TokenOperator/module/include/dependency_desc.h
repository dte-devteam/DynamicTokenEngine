#pragma once
#include <cvt/wstring>
#include "function/include/functionfactory.h"
namespace dependency_desc {
	enum class desc_type {
		function,
		constant,
		type
	};
	class module_version {
		friend bool operator >(module_version& ver1, module_version& ver2);
		friend bool operator ==(module_version& ver1, module_version& ver2);
		public:
			module_version(uint16_t v0 = 0, uint16_t v1 = 0, uint16_t v2 = 0, uint16_t v3 = 0);
			uint16_t* getversion();
		protected:
			uint16_t versionnumbers[4];
	};
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
	class function_requirement {
		public:
			function_requirement(uint64_t name, size_t index, desc_type desc_type);
			function_requirement(std::wstring name, size_t index, desc_type desc_type);
			uint64_t getname();
			size_t getindex();
			desc_type getdesctype();
		protected:
			uint64_t name;
			size_t index;
			desc_type type;
	};
	struct function_data {
		function_data(functionfactory::basicfunction* function, std::vector<function_requirement> requirements = {});
		functionfactory::basicfunction* function;
		std::vector<function_requirement> requirements;
		bool init_status;
	};
}