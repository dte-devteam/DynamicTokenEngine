#pragma once
#include "token/object.h"
#include <string.h>
#include <corecrt_malloc.h>
namespace tokenoperator::dte_token::data {
	template<typename V>
	struct type : object {
		public:
			type(uint64_t ID = 0) : object(ID) {
				name = _strdup(typeid(V).name());
				raw_name = _strdup(typeid(V).raw_name());
				hash_code = typeid(V).hash_code();
			}
			type(const type<V>& t) : object(t.ID) {
				name = _strdup(t.name); 
				raw_name = _strdup(t.raw_name); 
				hash_code = t.hash_code; 
			}
			type& operator=(const type<V>& t) {
				if (this == &t) {
					return *this;
				}
				free(name);
				free(raw_name);
				name = _strdup(t.name);
				raw_name = _strdup(t.raw_name);
				hash_code = t.hash_code;
				return *this;
			}
			~type() {
				free(name); 
				free(raw_name);
			}
			char* get_name() const { 
				return _strdup(name); 
			}
			char* get_raw_name() const { 
				return _strdup(raw_name); 
			}
			size_t get_hash() const {
				return hash_code; 
			}
		protected:
			//typeid output exists as long as RTTI does (need _strdup for copying)
			char* name;
			char* raw_name;
			size_t hash_code;
	};
}