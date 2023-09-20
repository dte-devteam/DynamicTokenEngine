#pragma once
#include "type.h"
namespace tokenoperator::dte_token::data {
	typedef object* (*create_value_function)(uint64_t);
	typedef object* (*copy_value_function)(object*, uint64_t);
	typedef std::pair<create_value_function, copy_value_function> value_functions;
	template<typename T>
	struct value : object {
		template <typename U> friend struct value;
		public:
			value(uint64_t ID = 0) : object(ID), t(ID) {}
			value(const T& v, uint64_t ID = 0) : object(ID), t(ID), v(v) {}
			template<typename U>
			value(const U& v, uint64_t ID = 0) : object(ID), t(ID), v(v) {}
			T& operator*() { 
				return v; 
			}
			T* operator->() {
				return &v; 
			}
			T* get_pointer() {
				return &v;
			}
			type<T> get_type() const { 
				return t;
			}
		protected:
			T v;
			type<T> t;
	};
	template<typename T>
	value<T>* create_value(uint64_t ID) { 
		return new value<T>(ID); 
	}
	template<typename T>
	value<T>* copy_value(object* source, uint64_t ID) {
		value<T>* new_value = new value<T>(ID);
		**new_value = **(value<T>*)source;
		return new_value;
	}
	template<typename T>
	value_functions create_copy_value_pair() {
		return std::make_pair((create_value_function)create_value<T>, (copy_value_function)copy_value<T>);
	}
}