#pragma once
#include "weak_ref.h"
namespace dte_utils {
	template<typename T>
	struct strong_ref : weak_ref<T> {
		template <typename U> friend struct strong_ref;
		protected:
			template<REF_ASSIGNABLE<T> U>
			strong_ref(ref<U>* r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
		public:
			strong_ref() noexcept : strong_ref(new ref<T>) {}
			strong_ref(ref_pointer<T> instance) noexcept : strong_ref(new ref<T>(instance)) {}
			strong_ref(const strong_ref& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			strong_ref(strong_ref&& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}

			template<REF_ASSIGNABLE<T> U>
			strong_ref(const weak_ref<U>& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			template<REF_ASSIGNABLE<T> U>
			strong_ref(weak_ref<U>&& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}

			~strong_ref() {
				strong_decrease();
			}

			strong_ref& operator=(ref_pointer<T> instance) {
				strong_decrease();
				if (--reference->weak_owners) {
					reference = new ref<T>(instance);
				}
				else {
					reference->instance = instance;
				}
				++reference->weak_owners;
				++reference->strong_owners;
				return *this;
			}

			strong_ref& operator=(const strong_ref& r){
				if (this == &r) {
					return *this;
				}
				strong_decrease();
				weak_decrease();
				reference = pull_weak_ref(r);
				++reference->weak_owners;
				++reference->strong_owners;
				return *this;
			}
			strong_ref& operator=(strong_ref&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				std::swap(reference, r.reference);
				return *this;
			}

			template<REF_ASSIGNABLE<T> U>
			strong_ref& operator=(const weak_ref<U>& r) {
				if (reinterpret_cast<weak_ref<U>*>(this) == &r) {
					return *this;
				}
				strong_decrease();
				weak_decrease();
				reference = pull_weak_ref(r);
				++reference->weak_owners;
				++reference->strong_owners;
				return *this;
			}
			
			template<REF_ASSIGNABLE<T> U>
			strong_ref& operator=(weak_ref<U>&& r) {
				if (reinterpret_cast<weak_ref<U>*>(this) == &r) {
					return *this;
				}
				strong_decrease();
				weak_decrease();
				reference = pull_weak_ref(r);
				++reference->weak_owners;
				++reference->strong_owners;
				return *this;
			}
	};
}