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
			weak_ref() noexcept : weak_ref((T*)nullptr) {}
			weak_ref(T* instance) noexcept : weak_ref(new ref<T>(instance, 1, 0)) {}
			weak_ref(const weak_ref<T>& r) noexcept : weak_ref(r.reference) {
				++reference->weak_owners;
			}
			weak_ref(weak_ref<T>&& r) noexcept : weak_ref(std::move(r.reference)) {}
			template<typename U>
			weak_ref(U* instance) noexcept : weak_ref(new ref<U>(instance, 1, 0)) {}
			template<typename U>
			weak_ref(const weak_ref<U>& r) noexcept : weak_ref(r.reference) {
				++reference->weak_owners;
			}
			template<typename U>
			weak_ref(weak_ref<U>&& r) noexcept : weak_ref(std::move(r.reference)) {}
			~weak_ref() {
				if (!--reference->weak_owners) {
					delete reference;
				}
			}
			//operators
			weak_ref<T>& operator=(const weak_ref<T>& r) noexcept {
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
			weak_ref<T>& operator=(const weak_ref<U>& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &ref) {
					return *this;
				}
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = (ref<T>*)ref.reference;
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
			T& operator*() const noexcept {
				return *reference->instance;
			}
			T* operator->() const noexcept {
				return reference->instance;
			}
			//move related methods
			void move(T* target) noexcept(
				std::is_nothrow_move_constructible_v<T> &
				std::is_nothrow_move_assignable_v<T>
			){
				*target = std::move(reference->instance);
				reference->instance = target;
			}
			//get methods
			T* get_pointer() const noexcept {
				return reference->instance;
			}
			size_t get_weak_owners() const noexcept {
				return reference->weak_owners;
			}
			size_t get_strong_owners() const noexcept {
				return reference->strong_owners;
			}
		protected:
			weak_ref(ref<T>* reference) noexcept : reference(reference) {}
			template<typename U>
			weak_ref(ref<U>* reference) noexcept : reference((ref<T>*)reference){
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
			strong_ref() noexcept : strong_ref(nullptr) {}
			strong_ref(T* instance) noexcept : weak_ref(new ref<T>(instance, 1, 1)) {}
			strong_ref(const weak_ref<T> r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			strong_ref(weak_ref<T>&& r) noexcept : weak_ref(std::move(r)) {
				++reference->strong_owners;
			}
			strong_ref(const strong_ref<T, is_array>& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			strong_ref(strong_ref<T, is_array>&& r) noexcept : weak_ref(std::move(r)) {
				++reference->strong_owners;
			}
			template<typename U>
			strong_ref(U* instance) noexcept : weak_ref(new ref<U>(instance, 1, 1)) {}
			template<typename U>
			strong_ref(const weak_ref<U> r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			template<typename U>
			strong_ref(weak_ref<U>&& r) noexcept : weak_ref(std::move(r)) {
				++reference->strong_owners;
			}
			template<typename U>
			strong_ref(const strong_ref<U, is_array>& r) noexcept : weak_ref(r) {
				++reference->strong_owners;
			}
			template<typename U>
			strong_ref(strong_ref<U, is_array>&& r) noexcept : weak_ref(std::move(r)) {
				++reference->strong_owners;
			}
			~strong_ref() {
				if (!--reference->strong_owners) {
					kill_instance();
				}
			}
			//operators
			strong_ref<T, is_array>& operator=(const strong_ref<T, is_array>& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
					weak_ref::~weak_ref();
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
				reference = std::move(r.reference);
				return *this;
			}
			template<typename U>
			strong_ref<U, is_array>& operator=(const strong_ref<U, is_array>& r) noexcept {
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
			void kill_instance() {
				if constexpr (is_array) {
					delete[] reference->instance;
				}
				else {
					delete reference->instance;
				}
			}
	};
}