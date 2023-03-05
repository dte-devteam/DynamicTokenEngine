#pragma once
#include "function/include/functionfactory.h"
namespace memory {
	namespace function {
		struct importfunctionstruct : functionfactory::typedfunction {
			using functionfactory::typedfunction::typedfunction;
		};
		struct createfunctionstruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
		};
		struct functionloaderstruct : functionfactory::muxfunction {
			using functionfactory::muxfunction::muxfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
		};
	}
}