#pragma once
#include "../../include/functionfactory.h"
using namespace functionfactory;
namespace functions {
	namespace pointer {
		struct point : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
		struct unpoint : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		};
	}
}