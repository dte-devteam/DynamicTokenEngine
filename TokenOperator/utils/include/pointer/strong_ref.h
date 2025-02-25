#pragma once
#include "weak_ref.h"
namespace dte_utils {
	template<typename T>
	struct strong_ref : weak_ref<T> {
		template <typename U> friend struct strong_ref;
		protected:
			template<ref_assignable<T> U>
			strong_ref(ref<U>* r) noexcept : weak_ref(r) {
				++this->reference->strong_owners;
			}
		public:
			strong_ref() noexcept : strong_ref(new ref<T>) {}
			strong_ref(ref_pointer<T> instance) noexcept : strong_ref(new ref<T>(instance)) {}
			strong_ref(const strong_ref& r) noexcept : weak_ref(r) {
				++this->reference->strong_owners;
			}
			strong_ref(strong_ref&& r) noexcept : weak_ref(r) {
				++this->reference->strong_owners;
			}

			template<ref_assignable<T> U>
			strong_ref(const weak_ref<U>& r) noexcept : weak_ref(r) {
				++this->reference->strong_owners;
			}
			template<ref_assignable<T> U>
			strong_ref(weak_ref<U>&& r) noexcept : weak_ref(r) {
				++this->reference->strong_owners;
			}

			~strong_ref() {
				this->strong_decrease();
			}

			strong_ref& operator=(ref_pointer<T> instance) {
				this->strong_decrease();
				if (--this->reference->weak_owners) {
					this->reference = new ref<T>(instance);
				}
				else {
					this->reference->instance = instance;
				}
				++this->reference->weak_owners;
				++this->reference->strong_owners;
				return *this;
			}

			strong_ref& operator=(const strong_ref& r){
				if (this == &r) {
					return *this;
				}
				this->strong_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				++this->reference->strong_owners;
				return *this;
			}
			strong_ref& operator=(strong_ref&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				this->strong_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				++this->reference->strong_owners;
				return *this;
			}

			template<ref_assignable<T> U>
			strong_ref& operator=(const weak_ref<U>& r) {
				if (reinterpret_cast<weak_ref<U>*>(this) == &r) {
					return *this;
				}
				this->strong_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				++this->reference->strong_owners;
				return *this;
			}
			
			template<ref_assignable<T> U>
			strong_ref& operator=(weak_ref<U>&& r) {
				if (reinterpret_cast<weak_ref<U>*>(this) == &r) {
					return *this;
				}
				this->strong_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				++this->reference->strong_owners;
				return *this;
			}
	};
}