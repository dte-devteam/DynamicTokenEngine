#pragma once
#include "value.h"
#include "complex_type.h"
namespace tokenoperator::dte_token::data {
	struct complex_value : value<object*> {
		public:
			complex_value(complex_type heap, uint64_t ID = 0);
			~complex_value();
		protected:
			complex_type heap;
	};
}