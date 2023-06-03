#pragma once
#include "../include/complex_type.h"
namespace tokenoperator::dte_token::data {
	struct complex_value : value<object**> {
		public:
			complex_value(complex_type heap, uint64_t ID = 0);
			complex_value(const complex_value& cv);
			~complex_value();
			//complex_value& operator=(const complex_value& cv);
		protected:
			complex_type heap;
	};
}