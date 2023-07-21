#pragma once
#include "token/data/include/scope_path.h"
/*
*iscritical defines if requirement must be met
*may be there is reason to recreate OR = { AND = { i1, i2, ... } ... } structure of "iscritical"
*/
namespace tokenoperator::dte_module {
	struct module_source_requirement : dte_token::data::value<void*> {
		friend struct module_source;
		public:
			module_source_requirement(void* target, dte_token::data::scope_path source, bool iscritical = true, uint64_t ID = 0);
			module_source_requirement(const module_source_requirement& msr);
			module_source_requirement() : module_source_requirement(0, dte_token::data::EMPTY_SCOPE_PATH(0)) {}
			dte_token::data::scope_path get_source();
			bool iscritical();
		protected:
			dte_token::data::scope_path source;
			bool critical;
	};
}