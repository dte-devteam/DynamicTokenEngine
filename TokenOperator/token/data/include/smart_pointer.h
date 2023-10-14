#pragma once
#include "value.h"
namespace tokenoperator::dte_token::data {
	template<typename T>
	struct smart_pointer : value<T*>{
		template <typename U> friend struct smart_pointer;
		public:
			smart_pointer(T* pointer = nullptr, uint64_t ID = 0) : value<T*>(ID), owner_num(new size_t[]{1}) {
				v = pointer;
				t = type<T>();
			}
			template<typename U>
			smart_pointer(U* pointer = nullptr, uint64_t ID = 0) : value<T*>(ID), owner_num(new size_t[]{ 1 }) {
				static_assert(
					std::is_base_of<T, U>::value,
					"can create smart_pointer<T> from U* only if: T is base of U"
				);
				v = (T*)pointer;
				t = type<U>();
			}
			smart_pointer(const smart_pointer<T>& sp) : value<T*>(sp.ID), owner_num(sp.owner_num) {
				v = sp.v;
				t = sp.t;
				++*owner_num;
			}
			template<typename U>
			smart_pointer(const smart_pointer<U>& sp) : value<T*>(sp.ID), owner_num(sp.owner_num) {
				static_assert(
					std::is_base_of<T, U>::value,
					"can create smart_pointer<T> from smart_pointer<U> only if: T is base of U"
				);
				t = sp.t;
				v = (T*)sp.v;
				++*owner_num;
			}
			~smart_pointer() {
				if (!--*owner_num) {
					delete v;
					delete[] owner_num;
				}
			}
			T& get_value() = delete;
			template<typename U>
			smart_pointer<T>& operator=(const smart_pointer<U>& sp) {
				static_assert(
					std::is_base_of<T, U>::value,
					"can set smart_pointer<T> from smart_pointer<U> only if: T is base of U"
				);
				if (this == (smart_pointer<T>*)&sp) {
					return *this;
				}
				if (v != sp.v) {
					if (!--*owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = (T*)sp.v;
					t = sp.t;
					owner_num = sp.owner_num;
					++*owner_num;
				}
				return *this;
			}
			smart_pointer<T>& operator=(const smart_pointer<T>& sp) {
				if (this == &sp) {
					return *this;
				}
				if (v != sp.v) {
					if (!--*owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = sp.v;
					if (t.get_hash() != sp.t.get_hash()) {
						t = sp.t;
					}
					owner_num = sp.owner_num;
					++*owner_num;
				}
				return *this;
			}
			template<typename U>
			smart_pointer<T>& operator=(U* pointer) {
				static_assert(
					std::is_base_of<T, U>::value,
					"can set smart_pointer<T> from U* only if: T is base of U"
				);
				if (v != (T*)pointer) {
					if (!-- * owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = (T*)pointer;
					t = type<U>();
					owner_num = new size_t[]{1};
				}
				return *this;
			}
			smart_pointer<T>& operator=(T* pointer) {
				if (v != pointer) {
					if (!--*owner_num) {
						delete v;
						delete[] owner_num;
					}
					//if there was child of base, we can rewrite to base - T didn`t changed, but actual type - yes
					type<T> target_type;
					if (t.get_hash() != target_type.get_hash()) {
						t = target_type;
					}
					v = pointer;
					owner_num = new size_t[]{1};
				}
				return *this;
			}
			template<typename U>
			bool operator==(const smart_pointer<U>& sp) {
				return owner_num == sp.owner_num;
			}
			template<typename U>
			bool operator!=(const smart_pointer<U>& sp) {
				return owner_num != sp.owner_num;
			}
			operator T*() const {
				return v;
			}
			T& operator*() const {
				return *v;
			}
			T* operator->() const {
				return v;
			}
			T* get_pointer() const {
				return v;
			}
			size_t get_owner_num() const {
				return *owner_num;
			}
		protected:
			size_t* owner_num;
	};
}