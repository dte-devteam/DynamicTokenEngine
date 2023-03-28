#pragma once
#include "typedfunction.h"
namespace function {
	struct subtypedfunction : typedfunction {
		using typedfunction::typedfunction;
		protected:
			bool checktypecompability(std::vector<void*>* types);
	};
}