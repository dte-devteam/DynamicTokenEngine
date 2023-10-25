#pragma once
#include "type.h"
#include <type_traits>
namespace tokenoperator::dte_token::data {
	template<typename T>
	struct value : object {
		//static_assert(!is_bounded_array<T>::value, "Please, don`t use value for arrays");
		static_assert(!std::is_array<T>::value, "Please, don`t use value for arrays, if it is required - use std::array wrap in value");
		public:
			value(uint64_t ID = 0) : object(ID), t(ID) {}
			value(const T& v, uint64_t ID = 0) : object(ID), t(ID), v(v) {}
			T& get_value() {
				return v;
			}
			type<T> get_type() const { 
				return t;
			}
		protected:
			T v;
			type<T> t;
	};
}