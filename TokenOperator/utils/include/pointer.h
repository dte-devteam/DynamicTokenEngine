#pragma once
#include <type_traits>
namespace dte_utils {
	template<typename T>
	struct ref {
		T* instance;
		size_t weak_owners;
	};
	template<typename T>
	struct weak_ref {
		template <typename U> friend struct weak_ref;
		public:
			weak_ref() noexcept : weak_ref((T*)nullptr) {}
			weak_ref(T* instance) noexcept : weak_ref(new ref<T>(instance, 1)) {}
			weak_ref(const weak_ref<T>& ref) noexcept : weak_ref(ref.reference) {
				++reference->weak_owners;
			}
			weak_ref(weak_ref<T>&& ref) noexcept : weak_ref(std::move(ref.reference)) {}
			template<typename U>
			weak_ref(U* instance) noexcept : weak_ref(new ref<U>(instance, 1)) {}
			template<typename U>
			weak_ref(const weak_ref<U>& ref) noexcept : weak_ref(ref.reference) {
				++reference->weak_owners;
			}
			template<typename U>
			weak_ref(weak_ref<U>&& ref) noexcept : weak_ref(std::move(ref.reference)) {}
			~weak_ref() {
				if (!--reference->weak_owners) {
					delete reference;
				}
			}
			//operators
			weak_ref<T> operator=(const weak_ref<T>& ref) noexcept {
				if (this == &ref) {
					return *this;
				}
				--reference->weak_owners;
				reference = ref.reference;
				++reference->weak_owners;
				return *this;
			}
			weak_ref<T> operator=(weak_ref<T>&& ref) noexcept {
				if (this == &ref) {
					return *this;
				}
				--reference->weak_owners;
				reference = std::move(ref.reference);
				return *this;
			}
			template<typename U>
			weak_ref<T> operator=(const weak_ref<U>& ref) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &ref) {
					return *this;
				}
				--reference->weak_owners;
				reference = (ref<T>*)ref.reference;
				++*weak_owners;
				return *this;
			}
			template<typename U>
			weak_ref<T> operator=(weak_ref<U>&& ref) noexcept {
				static_assert(
					std::is_base_of_v<T, U> | std::is_convertible_v<U, T>,
					"can create reference to T from U only if:\n - T is base of U\n - U is convertable to T"
				);
				if (this == &ref) {
					return *this;
				}
				--*weak_owners;
				reference = std::move(ref.reference);
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
			size_t get_weak_owners() const noexcept {
				return reference->weak_owners;
			}
			T* get_pointer() const noexcept {
				return reference->instance;
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
		template <typename U> friend struct weak_ref;
		public:
			strong_ref() noexcept : strong_ref(nullptr) {}
			strong_ref(T* instance) noexcept : weak_ref(instance), strong_owners(new size_t(1)) {}
			strong_ref(const weak_ref<T> ref) noexcept : weak_ref(ref), strong_owners(new size_t(1)) {}
			strong_ref(weak_ref<T>&& ref) noexcept : weak_ref(ref) noexcept {
				++*strong_owners;
			}
			strong_ref(const strong_ref<T, is_array>& ref) noexcept : weak_ref(ref), strong_owners(ref.strong_owners) {
				++*strong_owners;
			}
			strong_ref(strong_ref<T, is_array>&& ref) noexcept : weak_ref(std::move(ref.instance), std::move(ref.strong_owners)) {
				++*strong_owners;
			}
			~strong_ref() {
				if (!--*strong_owners) {
					if constexpr (is_array) {
						delete[] reference->instance;
					}
					else {
						delete reference->instance;
					}
					delete strong_owners;
					weak_ref::~weak_ref();
				}
			}
			//operators




			//get methods
			weak_ref<T> get_weak_ref() {
				return weak_ref(instance, owners);
			}
		protected:
			size_t* strong_owners;
	};
}