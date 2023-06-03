#pragma once
#include "type.h"
namespace tokenoperator::dte_token::data {
	typedef object* (*create_value_function)(uint64_t);
	typedef object* (*copy_value_function)(object*, uint64_t);
	template<typename V>
	struct value : object {
		public:
			value(uint64_t ID = 0) : object(ID), t(ID) {}
			V& operator*() { 
				return v; 
			}
			V* operator->() { 
				return &v; 
			}
			type<V> get_type() const { 
				return t;
			}
		protected:
			V v;
			type<V> t;
	};
	template<typename V>
	value<V>* create_value(uint64_t ID) { 
		return new value<V>(ID); 
	}
	template<typename V>
	value<V>* copy_value(object* source, uint64_t ID) {
		value<V>* new_value = new value<V>(ID);
		**new_value = **((value<V>*)source);
		return new_value;
	}
	template<typename V>
	std::pair<create_value_function, copy_value_function> create_copy_value_pair() {
		return std::make_pair((create_value_function)create_value<V>, (copy_value_function)copy_value<V>);
	}
}