#pragma once
#include <type_traits>
namespace dte_utils {
	template<typename T>
	struct ref {
		T* instance;
		size_t weak_owners;
		size_t strong_owners;
	};
	template<typename T>
	struct weak_ref {
		template <typename U> friend struct weak_ref;
		public:
			constexpr weak_ref() noexcept : weak_ref((T*)nullptr) {}
			constexpr weak_ref(T* instance) noexcept : weak_ref(new ref<T>(instance, 1, 0)) {}
			constexpr weak_ref(const weak_ref<T>& r) noexcept : weak_ref(r.reference) {
				++reference->weak_owners;
			}
			constexpr weak_ref(weak_ref<T>&& r) noexcept : weak_ref(std::move(r.reference)) {}
			template<typename U>
			constexpr weak_ref(U* instance) noexcept : weak_ref(new ref<U>(instance, 1, 0)) {}
			template<typename U>
			constexpr weak_ref(const weak_ref<U>& r) noexcept : weak_ref(r.reference) {
				++reference->weak_owners;
			}
			template<typename U>
			constexpr weak_ref(weak_ref<U>&& r) noexcept : weak_ref(std::move(r.reference)) {}
			~weak_ref() {
				if (!--reference->weak_owners) {
					delete reference;
				}
			}
			//operators
			weak_ref<T>& operator=(const weak_ref<T>& r) {
				if (this == &r) {
					return *this;
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = r.reference;
				++reference->weak_owners;
				return *this;
			}
			weak_ref<T>& operator=(weak_ref<T>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = std::move(r.reference);
				return *this;
			}
			template<typename U>
			weak_ref<T>& operator=(const weak_ref<U>& r) {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = (ref<T>*)r.reference;
				++reference->weak_owners;
				return *this;
			}
			template<typename U>
			weak_ref<T>& operator=(weak_ref<U>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = std::move((ref<T>*)r.reference);
				return *this;
			}
			constexpr T& operator*() const noexcept {
				return *reference->instance;
			}
			constexpr T* operator->() const noexcept {
				return reference->instance;
			}
			//move related methods
			void move(T* target) noexcept(
				std::is_nothrow_move_constructible_v<T> &&
				std::is_nothrow_move_assignable_v<T>
			){
				*target = std::move(reference->instance);
				reference->instance = target;
			}
			//get methods
			constexpr T* get_pointer() const noexcept {
				return reference->instance;
			}
			constexpr size_t get_weak_owners() const noexcept {
				return reference->weak_owners;
			}
			constexpr size_t get_strong_owners() const noexcept {
				return reference->strong_owners;
			}
		protected:
			constexpr weak_ref(ref<T>* reference) noexcept : reference(reference) {}
			template<typename U>
			constexpr weak_ref(ref<U>* reference) noexcept : reference((ref<T>*)reference) {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
			}
			ref<T>* reference;
	};
	template<typename T, bool is_array>
	struct strong_ref : weak_ref<T> {
		template <typename U, bool is_array> friend struct strong_ref;
		public:
			constexpr strong_ref() noexcept : strong_ref(nullptr) {}
			constexpr strong_ref(T* instance) noexcept : weak_ref<T>(new ref<T>(instance, 1, 1)) {}
			constexpr strong_ref(const weak_ref<T> r) noexcept : weak_ref<T>(r) {
				++reference->strong_owners;
			}
			constexpr strong_ref(weak_ref<T>&& r) noexcept : weak_ref<T>(std::move(r)) {
				++reference->strong_owners;
			}
			constexpr strong_ref(const strong_ref<T, is_array>& r) noexcept : weak_ref<T>(r) {
				++reference->strong_owners;
			}
			constexpr strong_ref(strong_ref<T, is_array>&& r) noexcept : weak_ref<T>(std::move(r)) {
				++reference->strong_owners;
			}
			template<typename U>
			constexpr strong_ref(U* instance) noexcept : weak_ref<T>(new ref<U>(instance, 1, 1)) {}
			template<typename U>
			constexpr strong_ref(const weak_ref<U> r) noexcept : weak_ref<T>(r) {
				++reference->strong_owners;
			}
			template<typename U>
			constexpr strong_ref(weak_ref<U>&& r) noexcept : weak_ref<T>(std::move(r)) {
				++reference->strong_owners;
			}
			template<typename U>
			constexpr strong_ref(const strong_ref<U, is_array>& r) noexcept : weak_ref<T>(r) {
				++reference->strong_owners;
			}
			template<typename U>
			constexpr strong_ref(strong_ref<U, is_array>&& r) noexcept : weak_ref<T>(std::move(r)) {
				++reference->strong_owners;
			}
			~strong_ref() {
				if (!--reference->strong_owners) {
					kill_instance();
				}
			}
			//operators
			strong_ref<T, is_array>& operator=(const strong_ref<T, is_array>& r) {
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
					weak_ref::~weak_ref();
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = r.reference;
				++reference->strong_owners;
				++reference->weak_owners;
				return *this;
			}
			strong_ref<T, is_array>& operator=(strong_ref<T, is_array>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
					weak_ref::~weak_ref();
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = std::move(r.reference);
				return *this;
			}
			template<typename U>
			strong_ref<U, is_array>& operator=(const strong_ref<U, is_array>& r) {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
					weak_ref::~weak_ref();
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = (ref<T>*)r.reference;
				++reference->strong_owners;
				++reference->weak_owners;
				return *this;
			}
			template<typename U>
			strong_ref<T, is_array>& operator=(strong_ref<U, is_array>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
					weak_ref::~weak_ref();
				}
				reference = std::move((ref<T>*)r.reference);
				return *this;
			}
		protected:
			void kill_instance() const noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if constexpr (is_array) {
					delete[] reference->instance;
				}
				else {
					delete reference->instance;
				}
			}
	};
	template<typename T, bool is_array>
	struct unknown_ref : weak_ref<T> {
		template<typename U, bool is_array> friend struct unknown_ref;
		public:
			template<typename ...Args>
			constexpr unknown_ref(bool strength, Args... args) noexcept : weak_ref<T>(args...), strength(strength) {
				if (strength) {
					++reference->strong_owners;
				}
			}
			constexpr unknown_ref(const unknown_ref<T, is_array>& r) noexcept : weak_ref<T>(r), strength(r.strength) {
				if (strength) {
					++reference->strong_owners;
				}
			}
			constexpr unknown_ref(unknown_ref<T, is_array>&& r) noexcept : weak_ref<T>(r), strength(std::move(r.strength)) {
				if (strength) {
					++reference->strong_owners;
				}
			}
			template<typename U>
			constexpr unknown_ref(const unknown_ref<U, is_array>& r) noexcept : weak_ref<T>(r), strength(r.strength) {
				if (strength) {
					++reference->strong_owners;
				}
			}
			template<typename U>
			constexpr unknown_ref(unknown_ref<U, is_array>&& r) noexcept : weak_ref<T>(r), strength(std::move(r.strength)) {
				if (strength) {
					++reference->strong_owners;
				}
			}
			~unknown_ref (){
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
			}
			void change_behavior() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				else {
					++reference->strong_owners;
				}
				strength = !strength;
			}
			//operators
			unknown_ref<T, is_array>& operator=(const unknown_ref<T, is_array>& r) {
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = r.reference;
				if (strength) {
					++reference->strong_owners;
				}
				++reference->weak_owners;
			}
			unknown_ref<T, is_array>& operator=(unknown_ref<T, is_array>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = std::move(r.reference);
			}
			template<typename U>
			unknown_ref<T, is_array>& operator=(const unknown_ref<U, is_array>& r) {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = (ref<T>*)r.reference;
				if (strength) {
					++reference->strong_owners;
				}
				++reference->weak_owners;
			}
			template<typename U>
			unknown_ref<T, is_array>& operator=(unknown_ref<U, is_array>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = std::move((ref<T>*)r.reference);
			}
			//get methods
			constexpr bool is_strong() const noexcept {
				return strength;
			}
		protected:
			bool strength;
			void kill_instance() const noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if constexpr (is_array) {
					delete[] reference->instance;
				}
				else {
					delete reference->instance;
				}
			}
	};
}