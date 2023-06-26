#pragma once
#include "value.h"
namespace tokenoperator::dte_token::data {
	template<typename T>
	struct smart_pointer : value<T*>{
		public:
			smart_pointer(T* pointer = nullptr, uint64_t ID = 0) : value<T*>(ID), owner_num(new size_t[]{1}) {
				v = pointer;
			}
			smart_pointer(const smart_pointer<T>& sop) : value<T*>(sop.ID), owner_num(sop.owner_num) {
				v = sop.v;
				++* owner_num;
			}
			~smart_pointer() {
				if (!-- * owner_num) {
					delete v;
					delete[] owner_num;
				}
			}
			smart_pointer& operator=(const smart_pointer<T>& sop) {
				if (this == &sop) {
					return *this;
				}
				ID = sop.ID;
				if (v != sop.v) {
					if (!-- * owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = sop.v;
					owner_num = sop.owner_num;
					++* owner_num;
				}
				return *this;
			}
			smart_pointer& operator=(T* pointer) {
				if (v != pointer) {
					if (!-- * owner_num) {
						delete v;
						delete[] owner_num;
					}
					v = pointer;
					owner_num = new size_t[]{ 1 };
				}
				return *this;
			}
			bool operator==(const smart_pointer<T>& sop) {
				return owner_num == sop.owner_num;
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