#pragma once
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
					strong_decrease();
				}
			}
			//behave as strong if it is strong at increase
			void unknown_increase() const {
				if (is_strong) {
					++reference->strong_owners;
				}
			}
			template<typename U>
			unknown_ref(ref<U>* r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
		public:
			unknown_ref(bool strength = false) noexcept : unknown_ref(new ref<T>(), strength) {}
			template<typename U = T>
			unknown_ref(ref_pointer<U> instance, bool strength = true) noexcept : unknown_ref(new ref<U>(instance), strength) {}
			template<typename U = T>
			unknown_ref(const weak_ref<U>& r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
			template<typename U = T>
			unknown_ref(weak_ref<U>&& r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
			~unknown_ref() {
				unknown_decrease();
			}
			//set stregth
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