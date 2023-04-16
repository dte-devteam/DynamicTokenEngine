#pragma once
#include <vector>
#include "function_requirement.h"
#include "function/include/basicfunction.h"
namespace module {
	template<class P, class R>
	struct export_data {
		export_data(P* pointer, std::vector<R> requirements = {}) : pointer(pointer), requirements(requirements), init_status(!requirements.size()) {}
		P* pointer;
		std::vector<R> requirements;
		bool init_status;
	};
	using function_data = export_data<function::basicfunction, function_requirement>;
}