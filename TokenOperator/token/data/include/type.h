#pragma once
#include "token/object.h"
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
		template <typename U> friend struct type;
		public:
			type(uint64_t ID = 0) : object(ID) {
				name = typeid(T).name();
				raw_name = typeid(T).raw_name();
				hash_code = typeid(T).hash_code();
			}
			template<typename U>
			type(const type<U>& ty) {
				name = ty.name;
				raw_name = ty.raw_name;
				hash_code = ty.hash_code;
			}
			template<typename U>
			type<T>& operator=(const type<U>& ty) {
				if (this == (type<T>*)&ty) {
					return *this;
				}
				name = ty.name;
				raw_name = ty.raw_name;
				hash_code = ty.hash_code;
				return *this;
			}
			bool operator==(const type<T>& t) {
				return hash_code == t.hash_code;
			}
			std::string get_name() const {
				return name; 
			}
			std::string get_raw_name() const {
				return raw_name; 
			}
			size_t get_hash() const {
				return hash_code; 
			}
		protected:
			std::string name;
			std::string raw_name;
			size_t hash_code;
	};
}