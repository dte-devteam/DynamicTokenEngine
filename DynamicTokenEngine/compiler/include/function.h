#pragma once
#include <vector>
#include "../../utils/include/hash.h"
namespace compiler {
	namespace function {
		uint64_t createtype(uint32_t realtype, bool isconst, bool ispointer);
	}
}