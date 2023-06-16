#pragma once
#include "token/object.h"
#include <xstring>
#include <corecrt_malloc.h>
#include <utility>
#include <memory>
#include <type_traits>
namespace tokenoperator::dte_token::data {
	template<class T>
	concept pointer = std::is_pointer<T>::value;
	//typeid output exists as long as RTTI does (so type will copy RTTI data)
	template<typename T>
	struct type : object {
		public:
			type(uint64_t ID = 0) : object(ID) {
				name = typeid(T).name();
				raw_name = typeid(T).raw_name();
				hash_code = typeid(T).hash_code();
			}
			bool operator==(const type<T>& t) {
				return hash_code == t.hash_code;
			}
			std::string get_name() {
				return name; 
			}
			std::string get_raw_name() {
				return raw_name; 
			}
			size_t get_hash() {
				return hash_code; 
			}
		protected:
			std::string name;
			std::string raw_name;
			size_t hash_code;
	};
}