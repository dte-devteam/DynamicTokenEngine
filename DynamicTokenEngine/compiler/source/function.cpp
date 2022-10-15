#include "../include/function.h"
namespace compiler {
	namespace function {
		uint64_t createtype(uint32_t realtype, bool isconst, bool ispointer) {
			uint64_t type = realtype;
			uint64_t desc_shift = 0x100000000;
			std::vector<bool> bools({ isconst, ispointer });
			for (bool b : bools) {
				if (b) {
					type |= desc_shift;
				}
				desc_shift = desc_shift << 1;
			}
			return type;
		}
	}
}