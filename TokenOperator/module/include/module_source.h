#pragma once
#include "module_source_requirement.h"
namespace tokenoperator::dte_module {
	template<dte_token::data::pointer T>
	struct module_source : dte_token::data::value<T> {
		public:
			//to do (add module_source_requirement)
			module_source(T source, uint64_t ID = 0);
		protected:
			bool init_status[2];
	};
}