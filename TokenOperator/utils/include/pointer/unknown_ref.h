#pragma once
#include <iostream>
#include "weak_ref.h"
namespace dte_utils {
	template<typename T>
	struct unknown_ref : weak_ref<T> {
		template <typename U> friend struct unknown_ref;
		protected:
			bool is_strong;
			//behave as strong if it is strong at decreasing
			void unknown_decrease() const {
				if (is_strong) {
					this->strong_decrease();
				}
			}
			//behave as strong if it is strong at increase
			void unknown_increase() const {
				if (is_strong) {
					++this->reference->strong_owners;
				}
			}
			template<ref_assignable<T> U>
			unknown_ref(ref<U>* r, bool strength) noexcept : is_strong(strength), weak_ref<T>(r) {
				unknown_increase();
			}
		public:
			unknown_ref(bool strength = false) noexcept : unknown_ref(new ref<T>(), strength) {}
			unknown_ref(ref_pointer<T> instance, bool strength = false) noexcept : unknown_ref(new ref<T>(instance), strength) {}
			
			unknown_ref(const unknown_ref& r, bool strength = false) noexcept : unknown_ref(r.reference, strength) {}
			unknown_ref(unknown_ref&& r) noexcept : unknown_ref(r.reference, r.is_strong) {}
			
			template<ref_assignable<T> U>
			unknown_ref(const weak_ref<U>& r, bool strength = false) noexcept : is_strong(strength), weak_ref<T>(r) {
				unknown_increase();
			}

			~unknown_ref() {
				unknown_decrease();
			}

			unknown_ref& operator=(ref_pointer<T> instance) {
				unknown_decrease();
				if (--this->reference->weak_owners) {
					this->reference = new ref<T>(instance);
				}
				else {
					this->reference->instance = instance;
				}
				++this->reference->weak_owners;
				unknown_increase();
				return *this;
			}

			unknown_ref& operator=(const unknown_ref& r) {
				if (this == &r) {
					return *this;
				}
				unknown_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				unknown_increase();
				return *this;
			}
			unknown_ref& operator=(unknown_ref&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (is_strong == r.is_strong) {
					ref<T>* buffer = this->pull_weak_ref(r);
					this->push_weak_ref(r, this->reference);
					this->reference = buffer;
				}
				else {
					unknown_decrease();
					this->weak_decrease();
					this->reference = this->pull_weak_ref(r);
					++this->reference->weak_owners;
					unknown_increase();
				}
				return *this;
			}

			template<ref_assignable<T> U>
			unknown_ref& operator=(const weak_ref<U>& r) {
				if (reinterpret_cast<weak_ref<U>*>(this) == &r) {
					return *this;
				}
				unknown_decrease();
				this->weak_decrease();
				this->reference = pull_weak_ref(r);
				++this->reference->weak_owners;
				unknown_increase();
				return *this;
			}
			//stregth
			bool get_strength() {
				return is_strong;
			}
			void set_strength(bool strength) {
				if (is_strong == strength) {
					return;
				}
				unknown_decrease();
				is_strong = strength;
				unknown_increase();
			}
	};
}