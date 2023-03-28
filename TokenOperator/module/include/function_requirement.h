#pragma once
#include <cvt/wstring>
#include "module_version.h"
#include "function/include/basicfunction.h"
namespace module {
	enum class desc_type {
		function,	//pointer for direct work with f()
		f_call,		//pointer for calling f() (NOT FOR basicfunction!!!)
		f_mux,		//pointer for mux function (ONLY FOR muxfunction!!!)
		data,		//pointer for data
		type		//pointer for type data
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
}