#pragma once
#include "token/data/include/value.h"
/*
*iscritical defines if requirement must be met
*may be there is reason to recreate OR = { AND = { i1, i2, ... } } structure of "iscritical"
*/
namespace tokenoperator::dte_module {
	struct module_source_requirement : dte_token::data::value<void*> {
		public:
			//to do (add name/path to source)
			module_source_requirement(void* target, bool iscritical = true, uint64_t ID = 0);
		protected:
			bool iscritical;
	};
}