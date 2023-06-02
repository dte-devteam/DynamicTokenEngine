#pragma once
#include "type.h"
namespace tokenoperator::dte_token::data {
	typedef object* (*create_value_function)(uint64_t);
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
}