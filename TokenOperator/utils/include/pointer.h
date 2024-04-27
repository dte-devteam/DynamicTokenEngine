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
			constexpr weak_ref<T>& operator=(const weak_ref<T>& r) {
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
			constexpr weak_ref<T>& operator=(weak_ref<T>&& r) noexcept {
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
			constexpr weak_ref<T>& operator=(const weak_ref<U>& r) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
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
			constexpr weak_ref<T>& operator=(weak_ref<U>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
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
			constexpr weak_ref<T>& operator=(T* instance) {
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = new ref<T>(instance, 1, 0);
			}
			template<typename U>
			constexpr weak_ref<T>& operator=(U* instance) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (!--reference->weak_owners) {
					delete reference;
				}
				reference = new ref<T>((T*)instance, 1, 0);
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
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
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
			constexpr strong_ref<T, is_array>& operator=(const strong_ref<T, is_array>& r) {
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = r.reference;
				++reference->strong_owners;
				++reference->weak_owners;
				return *this;
			}
			constexpr strong_ref<T, is_array>& operator=(strong_ref<T, is_array>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = std::move(r.reference);
				return *this;
			}
			template<typename U>
			constexpr strong_ref<U, is_array>& operator=(const strong_ref<U, is_array>& r) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = (ref<T>*)r.reference;
				++reference->strong_owners;
				++reference->weak_owners;
				return *this;
			}
			template<typename U>
			constexpr strong_ref<T, is_array>& operator=(strong_ref<U, is_array>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (this == &r) {
					return *this;
				}
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = std::move((ref<T>*)r.reference);
				return *this;
			}
			constexpr strong_ref<T, is_array>& operator=(T* instance) {
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = new ref<T>(instance, 1, 1);
			}
			template<typename U>
			constexpr strong_ref<T, is_array>& operator=(U* instance) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (!--reference->strong_owners) {
					kill_instance();
				}
				weak_ref::~weak_ref();
				reference = new ref<T>((T*)instance, 1, 1);
			}
		protected:
			constexpr void kill_instance() const noexcept(
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
			constexpr void change_behavior() noexcept(
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
			constexpr unknown_ref<T, is_array>& operator=(const unknown_ref<T, is_array>& r) {
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak()
				reference = r.reference;
				if (strength) {
					++reference->strong_owners;
				}
				++reference->weak_owners;
			}
			constexpr unknown_ref<T, is_array>& operator=(unknown_ref<T, is_array>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak()
				reference = std::move(r.reference);
			}
			template<typename U>
			constexpr unknown_ref<T, is_array>& operator=(const unknown_ref<U, is_array>& r) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak()
				reference = (ref<T>*)r.reference;
				if (strength) {
					++reference->strong_owners;
				}
				++reference->weak_owners;
			}
			template<typename U>
			constexpr unknown_ref<T, is_array>& operator=(unknown_ref<U, is_array>&& r) noexcept {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (this == &r) {
					return *this;
				}
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak()
				reference = std::move((ref<T>*)r.reference);
			}
			constexpr unknown_ref<T, is_array>& operator=(T* instance) {
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak();
				reference = new ref<T>(instance, 1, strength ? 1 : 0);
			}
			template<typename U>
			constexpr unknown_ref<T, is_array>& operator=(U* instance) {
				static_assert(
					std::is_base_of_v<T, U>,
					"can create reference to T from U only if T is base of U"
				);
				if (strength) {
					if (!--reference->strong_owners) {
						kill_instance();
					}
				}
				weak::~weak();
				reference = new ref<T>((T*)instance, 1, strength ? 1 : 0);
			}
			//get methods
			constexpr bool is_strong() const noexcept {
				return strength;
			}
		protected:
			bool strength;
			constexpr void kill_instance() const noexcept(
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
	enum class ref_type {
		none, weak, strong, strong_array, unknown, unknown_array
	};
	template<typename T>
	struct any_ref {
		//can be constexpr?
		template <typename U> friend struct any_ref;
		public:
			constexpr any_ref() : type(ref_type::none) {}
			constexpr any_ref(const weak_ref<T>& r) : type(ref_type::weak) {
				new (&u.weak) weak_ref<T>(r);
			}
			constexpr any_ref(const strong_ref<T, false>& r) : type(ref_type::strong) {
				new (&u.strong) strong_ref<T, false>(r);
			}
			constexpr any_ref(const strong_ref<T, true>& r) : type(ref_type::strong_array) {
				new (&u.strong_array) strong_ref<T, true>(r);
			}
			constexpr any_ref(const unknown_ref<T, false>& r) : type(ref_type::unknown) {
				new (&u.unknown) unknown_ref<T, false>(r);
			}
			constexpr any_ref(const unknown_ref<T, true>& r) : type(ref_type::unknown_array) {
				new (&u.unknown_array) unknown_ref<T, true>(r);
			}
			constexpr any_ref(const any_ref<T>& r) : type(r.type) {
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(r.u.weak);							break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(r.u.strong);				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(r.u.strong_array);	break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(r.u.unknown);			break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(r.u.unknown_array);	break;
				}
			}
			template<typename U>
			constexpr any_ref(const weak_ref<U>& r) : type(ref_type::weak) {
				new (&u.weak) weak_ref<T>(r);
			}
			template<typename U>
			constexpr any_ref(const strong_ref<U, false>& r) : type(ref_type::strong) {
				new (&u.strong) strong_ref<T, false>(r);
			}
			template<typename U>
			constexpr any_ref(const strong_ref<U, true>& r) : type(ref_type::strong_array) {
				new (&u.strong_array) strong_ref<T, true>(r);
			}
			template<typename U>
			constexpr any_ref(const unknown_ref<U, false>& r) : type(ref_type::unknown) {
				new (&u.unknown) unknown_ref<T, false>(r);
			}
			template<typename U>
			constexpr any_ref(const unknown_ref<U, true>& r) : type(ref_type::unknown_array) {
				new (&u.unknown_array) unknown_ref<T, true>(r);
			}
			template<typename U>
			constexpr any_ref(const any_ref<U>& r) : type(r.type) {
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(r.u.weak);							break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(r.u.strong);				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(r.u.strong_array);	break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(r.u.unknown);			break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(r.u.unknown_array);	break;
				}
			}
			constexpr any_ref(weak_ref<T>&& r) noexcept : type(ref_type::weak) {
				new (&u.weak) weak_ref<T>(r);
			}
			constexpr any_ref(strong_ref<T, false>&& r) noexcept : type(ref_type::strong) {
				new (&u.strong) strong_ref<T, false>(r);
			}
			constexpr any_ref(strong_ref<T, true>&& r) noexcept : type(ref_type::strong_array) {
				new (&u.strong_array) strong_ref<T, true>(r);
			}
			constexpr any_ref(unknown_ref<T, false>&& r) noexcept : type(ref_type::unknown) {
				new (&u.unknown) unknown_ref<T, false>(r);
			}
			constexpr any_ref(unknown_ref<T, true>&& r) noexcept : type(ref_type::unknown_array) {
				new (&u.unknown) unknown_ref<T, true>(r);
			}
			constexpr any_ref(any_ref<T>&& r) noexcept : type(std::move(r.type)) {
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(std::move(r.u.weak));								break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(std::move(r.u.strong));				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(std::move(r.u.strong_array));		break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(std::move(r.u.unknown));				break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(std::move(r.u.unknown_array));	break;
				}
			}
			template<typename U>
			constexpr any_ref(weak_ref<U>&& r) : type(ref_type::weak) noexcept {
				new (&u.weak) weak_ref<T>(r);
			}
			template<typename U>
			constexpr any_ref(strong_ref<U, false>&& r) : type(ref_type::strong) noexcept {
				new (&u.strong) strong_ref<T, false>(r);
			}
			template<typename U>
			constexpr any_ref(strong_ref<U, true>&& r) : type(ref_type::strong_array) noexcept {
				new (&u.strong_array) strong_ref<T, true>(r);
			}
			template<typename U>
			constexpr any_ref(unknown_ref<U, false>&& r) : type(ref_type::unknown) noexcept {
				new (&u.unknown) unknown_ref<T, false>(std::move(r));
			}
			template<typename U>
			constexpr any_ref(unknown_ref<U, true>&& r) : type(ref_type::unknown_array) noexcept {
				new (&u.unknown) unknown_ref<T, true>(std::move(r));
			}
			template<typename U>
			constexpr any_ref(any_ref<U>&& r) : type(std::move(r.type)) noexcept {
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(std::move(r.u.weak));								break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(std::move(r.u.strong));				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(std::move(r.u.strong_array));		break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(std::move(r.u.unknown));				break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(std::move(r.u.unknown_array));	break;
				}
			}
			~any_ref() {
				kill_ref();
			}
			//get methods
			constexpr ref_type get_type() {
				return type;
			}
			template<template<typename> typename C>
			constexpr C<T>* get_if() {}
			template<>
			constexpr weak_ref<T>* get_if<weak_ref>() {
				return type == ref_type::weak ? &u.weak : nullptr;
			}
			template<template<typename, bool> typename C, bool is_array>
			constexpr C<T, is_array>* get_if() {}
			template<>
			constexpr strong_ref<T, false>* get_if<strong_ref, false>() {
				return type == ref_type::strong ? &u.strong : nullptr;
			}
			template<>
			constexpr strong_ref<T, true>* get_if<strong_ref, true>() {
				return type == ref_type::strong_array ? &u.strong_array : nullptr;
			}
			template<>
			constexpr unknown_ref<T, false>* get_if<unknown_ref, false>() {
				return type == ref_type::unknown ? &u.unknown : nullptr;
			}
			template<>
			constexpr unknown_ref<T, true>* get_if<unknown_ref, true>() {
				return type == ref_type::unknown_array ? &u.unknown_array : nullptr;
			}
			template<template<typename> typename C>
			constexpr C<T>& get() {}
			template<>
			constexpr weak_ref<T>& get<weak_ref>() {
				if (type == ref_type::weak) {
					return u.weak;
				}
				throw std::exception("can`t get weak_ref<T>& from non weak type");
			}
			template<template<typename, bool> typename C, bool is_array>
			constexpr C<T, is_array>& get() {}
			template<>
			constexpr strong_ref<T, false>& get<strong_ref, false>() {
				if (type == ref_type::strong) {
					return u.strong;
				}
				throw std::exception("can`t get strong_ref<T, false>& from non strong type");
			}
			template<>
			constexpr strong_ref<T, true>& get<strong_ref, true>() {
				if (type == ref_type::strong_array) {
					return u.strong_array;
				}
				throw std::exception("can`t get strong_ref<T, true>& from non strong_array type");
			}
			template<>
			constexpr unknown_ref<T, false>& get<unknown_ref, false>() {
				if (type == ref_type::unknown) {
					return u.unknown;
				}
				throw std::exception("can`t get unknown_ref<T, false>& from non unknown type");
			}
			template<>
			constexpr unknown_ref<T, true>& get<unknown_ref, true>() {
				if (type == ref_type::unknown_array) {
					return u.unknown_array;
				}
				throw std::exception("can`t get unknown_ref<T, true>& from non unknown_array type");
			}
			//set_methods
			constexpr void clear() {
				kill_ref();
				type = none;
			}
			//operators-----------------------------
			constexpr any_ref<T>& operator=(const any_ref<T>& r) {
				if (this == &r) {
					return *this;
				}
				kill_ref();
				type = r.type;
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(r.u.weak);							break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(r.u.strong);				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(r.u.strong_array);	break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(r.u.unknown);			break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(r.u.unknown_array);	break;
				}
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const any_ref<U>& r) {
				if (this == &r) {
					return *this;
				}
				kill_ref();
				type = r.type;
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(r.u.weak);							break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(r.u.strong);				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(r.u.strong_array);	break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(r.u.unknown);			break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(r.u.unknown_array);	break;
				}
				return *this;
			}
			constexpr any_ref<T>& operator=(any_ref<T>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				kill_ref();
				type = std::move(r.type);
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(std::move(r.u.weak));								break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(std::move(r.u.strong));				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(std::move(r.u.strong_array));		break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(std::move(r.u.unknown));				break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(std::move(r.u.unknown_array));	break;
				}
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(any_ref<U>&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				kill_ref();
				type = std::move(r.type);
				switch (type) {
					case ref_type::weak:			new (&u.weak) weak_ref<T>(std::move(r.u.weak));								break;
					case ref_type::strong:			new (&u.strong) strong_ref<T, false>(std::move(r.u.strong));				break;
					case ref_type::strong_array:	new (&u.strong_array) strong_ref<T, true>(std::move(r.u.strong_array));		break;
					case ref_type::unknown:			new (&u.unknown) unknown_ref<T, false>(std::move(r.u.unknown));				break;
					case ref_type::unknown_array:	new (&u.unknown_array) unknown_ref<T, true>(std::move(r.u.unknown_array));	break;
				}
				return *this;
			}
			constexpr any_ref<T>& operator=(const weak_ref<T>& r) noexcept {
				kill_ref();
				type = ref_type::weak;
				new (&u.weak) weak_ref<T>(r);
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const weak_ref<U>& r) noexcept {
				kill_ref();
				type = ref_type::weak;
				new (&u.weak) weak_ref<T>(r);
				return *this;
			}
			constexpr any_ref<T>& operator=(weak_ref<T>&& r) noexcept {
				kill_ref();
				type = ref_type::weak;
				new (&u.weak) weak_ref<T>(std::move(r));
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(weak_ref<U>&& r) noexcept {
				kill_ref();
				type = ref_type::weak;
				new (&u.weak) weak_ref<T>(std::move(r));
				return *this;
			}
			constexpr any_ref<T>& operator=(const strong_ref<T, false>& r) noexcept {
				kill_ref();
				type = ref_type::strong;
				new (&u.strong) strong_ref<T, false>(r);
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const strong_ref<U, false>& r) noexcept {
				kill_ref();
				type = ref_type::strong;
				new (&u.strong) strong_ref<T, false>(r);
				return *this;
			}
			constexpr any_ref<T>& operator=(strong_ref<T, false>&& r) noexcept {
				kill_ref();
				type = ref_type::strong;
				new (&u.strong) strong_ref<T, false>(std::move(r));
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(strong_ref<U, false>&& r) noexcept {
				kill_ref();
				type = ref_type::strong;
				new (&u.strong) strong_ref<T, false>(std::move(r));
				return *this;
			}
			constexpr any_ref<T>& operator=(const strong_ref<T, true>& r) noexcept {
				kill_ref();
				type = ref_type::strong_array;
				new (&u.strong_array) strong_ref<T, true>(r);
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const strong_ref<U, true>& r) noexcept {
				kill_ref();
				type = ref_type::strong_array;
				new (&u.strong_array) strong_ref<T, true>(r);
				return *this;
			}
			constexpr any_ref<T>& operator=(strong_ref<T, true>&& r) noexcept {
				kill_ref();
				type = ref_type::strong_array;
				new (&u.strong_array) strong_ref<T, true>(std::move(r));
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(strong_ref<U, true>&& r) noexcept {
				kill_ref();
				type = ref_type::strong_array;
				new (&u.strong_array) strong_ref<T, true>(std::move(r));
				return *this;
			}
			constexpr any_ref<T>& operator=(const unknown_ref<T, false>& r) noexcept {
				kill_ref();
				type = ref_type::unknown;
				new (&u.unknown) unknown_ref<T, false>(r);
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const unknown_ref<U, false>& r) noexcept {
				kill_ref();
				type = ref_type::unknown;
				new (&u.unknown) unknown_ref<T, false>(r);
				return *this;
			}
			constexpr any_ref<T>& operator=(unknown_ref<T, false>&& r) noexcept {
				kill_ref();
				type = ref_type::unknown;
				new (&u.unknown) unknown_ref<T, false>(std::move(r));
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(unknown_ref<U, false>&& r) noexcept {
				kill_ref();
				type = ref_type::unknown;
				new (&u.unknown) unknown_ref<T, false>(std::move(r));
				return *this;
			}
			constexpr any_ref<T>& operator=(const unknown_ref<T, true>& r) noexcept {
				kill_ref();
				type = ref_type::unknown_array;
				new (&u.unknown_array) unknown_ref<T, true>(r);
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(const unknown_ref<U, true>& r) noexcept {
				kill_ref();
				type = ref_type::unknown_array;
				new (&u.unknown_array) unknown_ref<T, true>(r);
				return *this;
			}
			constexpr any_ref<T>& operator=(unknown_ref<T, true>&& r) noexcept {
				kill_ref();
				type = ref_type::unknown_array;
				new (&u.unknown_array) unknown_ref<T, true>(std::move(r));
				return *this;
			}
			template<typename U>
			constexpr any_ref<T>& operator=(unknown_ref<U, true>&& r) noexcept {
				kill_ref();
				type = ref_type::unknown_array;
				new (&u.unknown_array) unknown_ref<T, true>(std::move(r));
				return *this;
			}
			constexpr bool operator==(const any_ref<T>& r) {
				if (type != r.type) {
					return false;
				}
				switch (type) {
					case ref_type::weak:			return u.weak == r.u.weak;
					case ref_type::strong:			return u.strong == r.u.strong;
					case ref_type::strong_array:	return u.strong_array == r.u.strong_array;
					case ref_type::unknown:			return u.unknown == r.u.unknown;
					case ref_type::unknown_array:	return u.unknown_array == r.u.unknown_array;
				}
			};
			constexpr bool operator==(any_ref<T>&& r) {
				if (type != r.type) {
					return false;
				}
				switch (type) {
					case ref_type::weak:			return u.weak == r.u.weak;
					case ref_type::strong:			return u.strong == r.u.strong;
					case ref_type::strong_array:	return u.strong_array == r.u.strong_array;
					case ref_type::unknown:			return u.unknown == r.u.unknown;
					case ref_type::unknown_array:	return u.unknown_array == r.u.unknown_array;
				}
			};
		protected:
			union ref_union {
				constexpr ref_union() noexcept {}
				~ref_union() {}
				weak_ref<T>				weak;
				strong_ref<T, false>	strong;
				strong_ref<T, true>		strong_array;
				unknown_ref<T, false>	unknown;
				unknown_ref<T, true>	unknown_array;
			} u;
			ref_type type;
			constexpr void kill_ref() noexcept {
				switch (type) {
					case ref_type::weak:			u.weak.~weak_ref<T>();						break;
					case ref_type::strong:			u.strong.~strong_ref<T, false>();			break;
					case ref_type::strong_array:	u.strong_array.~strong_ref<T, true>();		break;
					case ref_type::unknown:			u.unknown.~unknown_ref<T, false>();			break;
					case ref_type::unknown_array:	u.unknown_array.~unknown_ref<T, true>();	break;
				}
			}
	};
}