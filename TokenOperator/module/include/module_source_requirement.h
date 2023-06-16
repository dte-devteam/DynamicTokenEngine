#pragma once
#include "token/data/include/value.h"
#include "token/data/include/scope_path.h"
/*
*iscritical defines if requirement must be met
*may be there is reason to recreate OR = { AND = { i1, i2, ... } } structure of "iscritical"
*/
namespace tokenoperator::dte_module {
	template<dte_token::data::pointer T>
	struct module_source_requirement : dte_token::data::value<T> {
		public:
			module_source_requirement(T target, dte_token::data::scope_path source, bool iscritical = true, uint64_t ID = 0) : dte_token::data::value<T>(ID), source(source), iscritical(iscritical) {
				v = target;
			}
			module_source_requirement(const module_source_requirement<T>& msr) : dte_token::data::value<T>(msr.ID), source(msr.source), iscritical(msr.iscritical) {
				v = msr.v;
			}
		protected:
			dte_token::data::scope_path source;
			bool iscritical;
	};
}