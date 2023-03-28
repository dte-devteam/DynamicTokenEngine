#include "../include/function_data.h"
namespace module {
	function_data::function_data(function::basicfunction* function, std::vector<function_requirement> requirements) : function(function), requirements(requirements), init_status(!requirements.size()) {}
}