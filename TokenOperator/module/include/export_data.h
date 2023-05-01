#pragma once
#include <vector>
#include "export_requirement.h"
#include "function/include/basicfunction.h"
#include "data/include/value.h"
namespace module {
	template<class P>
	struct export_data {
		export_data(P* pointer, std::vector<export_requirement> requirements = {}) : pointer(pointer), requirements(requirements), init_status(!requirements.size()){
			stack_status = init_status;
		}
		P* pointer;
		std::vector<export_requirement> requirements;
		bool init_status;
		bool stack_status;
	};
	using function_data = export_data<function::basicfunction>;
	using value_data = export_data<data::value>;
}