#pragma once
#include "token/object.h"
#include "type.h"
namespace tokenoperator::token::data {
	template<class V>
	struct value : object {
		public:
			value(uint64_t ID) : object(ID), t(ID) {}
			//will behave like a pointer
			V& operator *() { return v; }
			V* operator->() { return &v; }
			type<V> t;
		protected:
			V v;
			//type<V> t;
	};
	template<class V>
	value<V>* create(uint64_t ID) { return new value<V>(ID); }
}