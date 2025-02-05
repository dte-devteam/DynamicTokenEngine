#pragma once
#include "weak_ref.h"
namespace dte_utils {
	template<typename T>
	struct strong_ref : weak_ref<T> {
		template <typename U> friend struct strong_ref;
		protected:
			template<typename U>
			strong_ref(ref<U>* r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
		public:
			strong_ref() noexcept : strong_ref(new ref<T>()) {}
			template<typename U = T>
			strong_ref(ref_pointer<U> instance) noexcept : strong_ref(new ref<U>(instance)) {}
			template<typename U = T>
			strong_ref(const weak_ref<U>& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			template<typename U = T>
			strong_ref(weak_ref<U>&& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			~strong_ref() {
				strong_decrease();
			}
	};
}