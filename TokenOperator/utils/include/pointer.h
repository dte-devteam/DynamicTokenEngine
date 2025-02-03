#pragma once
#include <type_traits>
#include "function.h"
namespace dte_utils {
	template<typename T>
	using ref_pointer = std::conditional_t<
		std::is_function_v<T>, 
		T, 
		std::conditional_t<
			std::is_array_v<T>, 
			std::decay_t<T>,
			T*
		>
	>;
	template<typename T>
	struct ref {
		ref_pointer<T> instance;
		size_t weak_owners;
		size_t strong_owners;
		constexpr ref(ref_pointer<T> instance = nullptr) noexcept : instance(instance), weak_owners(0), strong_owners(0) {}
	};
	template<typename T>
	struct weak_ref {
		template <typename U> friend struct weak_ref;
		protected:
			ref<T>* reference;
			constexpr void weak_decrease() const {
				if (!--reference->weak_owners) {
					delete reference;
				}
			}
			template<typename U>
			constexpr weak_ref(ref<U>* r) noexcept : reference((ref<T>*)r) {
				++reference->weak_owners;
				static_assert(
					std::is_array_v<T> == std::is_array_v<U> &&
					(
						std::is_same_v<ref_pointer<T>, ref_pointer<U>> ||
						std::is_base_of_v<T, U>
					)
					, "TODO: array pointer can be set only by array and vice versa"
				);
			}
		public:
			constexpr weak_ref() noexcept : weak_ref(new ref<T>()) {}
			template<typename U = T>
			constexpr weak_ref(ref_pointer<U> instance) noexcept : weak_ref(new ref<U>(instance)) {}
			template<typename U = T>
			constexpr weak_ref(const weak_ref<U>& r) noexcept : weak_ref(r.reference) {}
			template<typename U = T>
			constexpr weak_ref(weak_ref<U>&& r) noexcept : weak_ref(r.reference) {}
			~weak_ref() {
				weak_decrease();
			}
			constexpr size_t get_weak_owners() const {
				return reference->weak_owners;
			}
			constexpr size_t get_strong_owners() const {
				return reference->weak_owners;
			}
	};
	template<typename T>
	struct strong_ref : weak_ref<T> {
		template <typename U> friend struct strong_ref;
		protected:
			constexpr void strong_decrease() const {
				if constexpr (std::is_function_v<T>) {
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
			constexpr strong_ref(ref<U>* r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
		public:
			constexpr strong_ref() noexcept : strong_ref(new ref<T>()) {}
			template<typename U = T>
			constexpr strong_ref(ref_pointer<U> instance) noexcept : strong_ref(new ref<U>(instance)) {}
			template<typename U = T>
			constexpr strong_ref(const weak_ref<U>& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			template<typename U = T>
			constexpr strong_ref(weak_ref<U>&& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			~strong_ref() {
				strong_decrease();
			}
	};
	template<typename T>
	struct unknown_ref : weak_ref<T> {
		template <typename U> friend struct unknown_ref;
		protected:
			bool is_strong;
			constexpr void unknown_decrease() const {
				if (is_strong) {
					if constexpr (std::is_function_v<T>) {
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
			}
			constexpr void unknown_increase() const {
				if (is_strong) {
					++reference->strong_owners;
				}
			}
			template<typename U>
			constexpr unknown_ref(ref<U>* r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
		public:
			constexpr unknown_ref(bool strength = false) noexcept : unknown_ref(new ref<T>(), strength) {}
			template<typename U = T>
			constexpr unknown_ref(ref_pointer<U> instance, bool strength = true) noexcept : unknown_ref(new ref<U>(instance), strength) {}
			template<typename U = T>
			constexpr unknown_ref(const weak_ref<U>& r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
			template<typename U = T>
			constexpr unknown_ref(weak_ref<U>&& r, bool strength) noexcept : is_strong(strength), weak_ref(r) {
				unknown_increase();
			}
			~unknown_ref() {
				unknown_decrease();
			}
			constexpr void set_strength(bool strength) {
				unknown_increase();
				is_strong = strength;
				unknown_decrease();
			}
	};
}