#pragma once
#include "type.h"
namespace tokenoperator::dte_token::data {
	template<typename T>
	struct value : object {
		template <typename U> friend struct value;
		public:
			value(uint64_t ID = 0) : object(ID), t(ID) {}
			template<typename U>
			value(const U& v, uint64_t ID = 0) : object(ID), t(ID), v(v) {}
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