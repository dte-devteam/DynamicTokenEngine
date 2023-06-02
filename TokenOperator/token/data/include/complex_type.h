#pragma once
#include "../include/value.h"
#include <utility>
#include <memory>
namespace tokenoperator::dte_token::data {
	struct complex_type : value<std::pair<type<void>, create_value_function>*> {
		public:
			complex_type(size_t fields_to_add, object* types_to_add, create_value_function* constructors_of_types, uint64_t ID = 0);
			complex_type(const complex_type& ct);
			complex_type(const complex_type& ct1, const complex_type& ct2, uint64_t ID = 0);
			~complex_type();
			complex_type& operator=(const complex_type& ct);
			size_t get_number_of_fields();
		protected:
			size_t number_of_fields;
	};
}