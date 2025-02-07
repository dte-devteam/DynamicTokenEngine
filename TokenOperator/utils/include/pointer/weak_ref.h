#pragma once
#include "ref.h"
namespace dte_utils {
	template<typename T>
	struct weak_ref {
		template <typename U> friend struct weak_ref;
		protected:
			ref<T>* reference;
			//decrease weak owners and if this is the last one - kill reference
			void weak_decrease() const {
				if (!--reference->weak_owners) {
					delete reference;
				}
			}
			//decrease strong owners and if this is the last one - kill instance
			void strong_decrease() const {
				if constexpr (return_type_v<T>) {
					!--reference->strong_owners;
				}
				else if constexpr (std::is_array_v<T>) {
					if (!--reference->strong_owners) {
						delete[] reference->instance;
					}
				}
				else {
					if (!--reference->strong_owners) {
						delete reference->instance;
					}
				}
			}
			template<typename U>
			void fetch_weak_ref(const weak_ref<U>& r) {
				REF_ASSIGN_LIMITS
				reference = (ref<T>*)r.reference;
			}
			template<typename U>
			weak_ref(ref<U>* r) noexcept : reference((ref<T>*)r) {
				REF_ASSIGN_LIMITS
				++reference->weak_owners;
			}
		public:
			weak_ref() noexcept : weak_ref(new ref<T>()) {}
			template<typename U = T>
			weak_ref(ref_pointer<U> instance) noexcept : weak_ref(new ref<U>(instance)) {}
			template<typename U = T>
			weak_ref(const weak_ref<U>& r) noexcept : weak_ref(r.reference) {}
			template<typename U = T>
			weak_ref(weak_ref<U>&& r) noexcept : weak_ref(r.reference) {}
			~weak_ref() {
				weak_decrease();
			}
			template<typename U = T>
			weak_ref& operator=(ref_pointer<U> instance) {
				REF_ASSIGN_LIMITS
				if (!--reference->weak_owners) {
					reference->instance = (ref_pointer<T>)instance;
				}
				else {
					reference = (ref<T>*)new ref<U>(instance);
				}
				++reference->weak_owners;
				return *this;
			}
			template<typename U = T>
			weak_ref& operator=(const weak_ref<U>& r) {
				REF_ASSIGN_LIMITS
				if (this == (weak_ref*)&r) {
					return *this;
				}
				weak_decrease();
				reference = (ref<T>*)r.reference;
				++reference->weak_owners;
				return *this;
			}
			weak_ref& operator=(weak_ref&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				std::swap(reference, r.reference);
				return *this;
			}
			size_t get_weak_owners() const {
				return reference->weak_owners;
			}
			size_t get_strong_owners() const {
				return reference->weak_owners;
			}
			ref_pointer<T> get_pointer() const {
				return reference->instance;
			}
			template<typename R = return_type_t<T>, typename ...Args>
			R operator()(Args&&... args) const {
				return reference->instance(args...);
			}
			template<typename U = std::enable_if_t<ref_instantiable<T>, T>>
			U& operator*() const {
				return *reference->instance;
			}
			template<typename U = std::enable_if_t<ref_instantiable<T>, T>>
			U* operator->() const {
				return reference->instance;
			}
			template<typename U = std::enable_if_t<std::is_array_v<T>, decltype(std::declval<T>()[0])>>
			U& operator[](size_t index) const {
				return reference->instance[index];
			}
	};
}