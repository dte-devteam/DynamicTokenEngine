#pragma once
#include "value.h"
#include <utility>
#include <memory>
namespace tokenoperator::dte_token::data {
	//use this define to create new complex type (that doesn`t inherit any other complex type)
	#define NEW_COMPLEX_TYPE(fields_to_add, types_to_add, constructors_of_types, ID) complex_type().generate_child(fields_to_add, types_to_add, constructors_of_types, ID)
	//sizeof(type<V>) always has 1 result, so we can store type with any V
	struct complex_type : value<std::pair<type<void>, create_value_function>*> {
		public:
			complex_type(uint64_t ID = 0);
			complex_type(const complex_type& ct);
			~complex_type();
			//complex_type& operator =(const complex_type& ct);
			size_t get_number_of_fields() const;
			complex_type generate_child(size_t fields_to_add, object* types_to_add, create_value_function* constructors_of_types, uint64_t ID = 0) const;
		protected:
			size_t number_of_fields = 0;
	};
}