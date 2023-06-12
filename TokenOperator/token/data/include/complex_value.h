#pragma once
#include "complex_type.h"
#include "scope.h"
namespace tokenoperator::dte_token::data {
	struct complex_value : scope {
		public:
			complex_value(complex_type heap, uint64_t ID = 0);
			complex_value(const complex_value& cv);
			~complex_value();
			//complex_value& operator=(const complex_value& cv);
		protected:
			complex_type heap;
	};
}