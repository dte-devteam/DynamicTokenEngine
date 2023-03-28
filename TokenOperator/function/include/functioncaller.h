#pragma once
#include "basicfunction.h"
namespace function {
	struct functioncaller {
		basicfunction* functionpointer;
		std::vector<std::pair<size_t, bool>> args_indices;
	};
}