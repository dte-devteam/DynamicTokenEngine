#pragma once
#include "value.h"

#include <iostream>
namespace tokenoperator::dte_token::data {
	template<typename T>
	struct smart_pointer : value<T*>{
		template <typename U> friend struct smart_pointer;
		public:
			smart_pointer(T* pointer = nullptr, uint64_t ID = 0) : value<T*>(ID), owner_num(new size_t[]{1}) {
				v = pointer;
			}
			smart_pointer(const smart_pointer<T>& sp) : value<T*>(sp.ID), owner_num(sp.owner_num) {
				v = sp.v;
				++*owner_num;
			}
			template<typename U>
			smart_pointer(const smart_pointer<U>& sp) : value<T*>(sp.getID()), owner_num(sp.owner_num) {
				static_assert(
					std::is_convertible<U, T>::value || std::is_base_of<T, U>::value,
					"can create smart_pointer<T> from smart_pointer<U> only if: T and U are convertible or T is base of U"
				);
				v = static_cast<T*>(sp.v);
				++*owner_num;
			}
			~smart_pointer() {
				if (!--*owner_num) {
					delete v;
					delete[] owner_num;
				}
			}
			smart_pointer& operator=(const smart_pointer<T>& sp) {
				if (this == &sp) {
					return *this;
				}
				if (v != sp.v) {
					if (!--*owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = sp.v;
					owner_num = sp.owner_num;
					++*owner_num;
				}
				return *this;
			}
			smart_pointer& operator=(T* pointer) {
				if (v != pointer) {
					if (!--*owner_num) {
						delete v;
						delete[] owner_num;
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
			//smart_pointer(const smart_pointer<T>& sp);
	};
}