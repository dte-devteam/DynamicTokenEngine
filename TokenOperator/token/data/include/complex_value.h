#pragma once
#include "complex_type.h"
#include "scope.h"
namespace tokenoperator::dte_token::data {
	struct complex_value : scope {
		public:
			complex_value(complex_type heap, uint64_t ID = 0);
			complex_value(const complex_value& cv);
			smart_object_pointer deep_copy(uint64_t copy_ID = 0, uint64_t pointer_ID = 0);
		protected:
			complex_value(complex_value* cv, uint64_t ID); //for deep_copy only
			complex_type heap;
	};
}