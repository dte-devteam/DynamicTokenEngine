#pragma once
#include "function_requirement.h"
namespace module {
	struct function_data {
		function_data(function::basicfunction* function, std::vector<function_requirement> requirements = {});
		function::basicfunction* function;
		std::vector<function_requirement> requirements;
		bool init_status;
	};
}