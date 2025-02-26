#pragma once
#include "memory.h"
#include <iostream>
namespace dte_utils {
	template<typename T>
	concept dyn_memory_limit = !(
			std::is_void_v<T> || 
			std::is_unbounded_array_v<T>
		);
	/*
	Operates with non-new array
	*/
	template<dyn_memory_limit T>
	struct dynamic_stack {
		template<dyn_memory_limit U> friend struct dynamic_stack;
		//protected:
			size_t	us;	//used size
			size_t	as;	//allocated size
			T*		a;	//array
			//us value MUST be in range of array! 
			void destruct_array() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(begin(), end());
				}
				free(a);
			}
			void provide_element_space() {
				if (as == us) {
					resize_allocated(as * 2 + 1);
				}
			}
		public:
			dynamic_stack() noexcept : us(0), as(0), a(nullptr) {}
			dynamic_stack(size_t alocate_size) noexcept : us(0), as(alocate_size), a(as ? malloc_t<T>(as) : nullptr) {}
			template<copy_constructible<T> U, size_t N>
			dynamic_stack(const U (&array)[N], size_t reserved_size = 0) noexcept : dynamic_stack(array, N, reserved_size) {}
			template<copy_constructible<T> U>
			dynamic_stack(const U* array, size_t used_size, size_t reserved_size) noexcept : us(used_size), as(us + reserved_size), a(malloc_t<T>(as)) {
				copy_array(a, array, us);
			}

			dynamic_stack(const dynamic_stack& dyn_array) noexcept : us(dyn_array.us), as(dyn_array.as), a(as ? malloc_t<T>(as) : nullptr) {
				copy_array(a, dyn_array.a, us);
			}
			dynamic_stack(dynamic_stack&& dyn_array) noexcept : us(dyn_array.us), as(dyn_array.as), a(dyn_array.a) {
				dyn_array.us = 0;
				dyn_array.a = nullptr;
			}

			template<copy_constructible<T> U>
			dynamic_stack(const dynamic_stack<U>& dyn_array) noexcept : us(dyn_array.us), as(dyn_array.as), a(as ? malloc_t<T>(as) : nullptr) {
				copy_array(a, dyn_array.a, us);
			}
			template<copy_constructible<T> U>
			dynamic_stack(dynamic_stack<U>&& dyn_array) noexcept : us(dyn_array.us), as(dyn_array.as), a(as ? malloc_t<T>(as) : nullptr) {
				copy_array(a, dyn_array.a, us);
			}

			~dynamic_stack() {
				destruct_array();
			}

			//for(T& t : dyn_array)
			T* begin() const {
				return a;
			}
			T* end() const {
				return a + us;
			}
			//
			template<typename P>
			T* find(P predicate) const {
				T* i = end();
				while (i != a) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			template<typename P>
			T* find_ranged(P predicate, size_t from, size_t to) const {
				//TODO: range can be outside of array (error)
				T* i = a + to;
				T* s = a + from;
				while (i != s) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			//doesn`t applyable for insert operation
			void resize_allocated(size_t size) {
				//TODO
				if (!size) {
					destruct_array();
					us = as = 0;
					a = nullptr;
					return;
				}
				if (us > size) {
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(a + size, end());
					}
					us = size;
				}
				if (as != size) {
					if constexpr (std::is_trivially_move_constructible_v<T>) {
						a = realloc_t<T>(a, size);
					}
					else {
						T* buffer = malloc_t<T>(size);
						std::swap(a, buffer);
						copy_array(a, buffer, us);
						if constexpr (!std::is_trivially_destructible_v<T>) {
							destruct_range(buffer, buffer + us);
						}
						free(buffer);
					}
					as = size;
				}
			}
			void clear() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(a, end());
				}
				us = 0;
			}
			//----------------
			template<copy_constructible<T> U>
			void push_back(const U& value) {
				provide_element_space();
				std::cout << us << " " << as << std::endl;
				if constexpr (std::is_trivially_constructible_v<T, const U&>) {
					a[us] = static_cast<T>(value);
				}
				else {
					new (end()) T(static_cast<T>(value));
				}
				++us;
			}
			template<move_constructible<T> U>
			void push_back(U&& value) {
				provide_element_space();
				//if constexpr (std::is_trivially_constructible_v<T, U&&>) {
				//	a[us] = static_cast<T&&>(value);
				//}
				//else {
					new (end()) T(static_cast<T&&>(value));
				//}
				++us;
			}
			template<typename ...Args>
			void emplace(Args&&... args) requires std::is_constructible_v<T, Args&&...> && !std::is_trivially_constructible_v<T, Args&&...> {
				provide_element_space();
				new (end()) T(std::forward<Args>(args)...);
				++us;
			}
			void pop_back() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					(a + --us)->~T();
				}
				else {
					--us;
				}
			}
			//----------------
			T& operator[](size_t index) {
				return a[index];
			}
			const T& operator[](size_t index) const {
				return a[index];
			}
			//assing operators


			dynamic_stack& operator =(const dynamic_stack& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				destruct_array();
				us = dyn_array.us;
				as = dyn_array.as;
				a = malloc_t<T>(as);
				copy_array(a, dyn_array.a, us);
				return *this;
			}
			dynamic_stack& operator =(dynamic_stack&& dyn_array) noexcept {
				if (this == &dyn_array) {
					return *this;
				}
				std::swap(a, dyn_array.a);
				std::swap(as, dyn_array.as);
				std::swap(us, dyn_array.us);
				return *this;
			}
			
			dynamic_stack& operator +=(const dynamic_stack& dyn_array) {
				if (as < us + dyn_array.us) {
					resize_allocated(us + dyn_array.us);
				}
				copy_array(a + us, dyn_array.a, dyn_array.us);
				us += dyn_array.us;
				return *this;
			}
			//dynamic_stack& operator +=(dynamic_stack&& dyn_array) {
			//	if (as < us + dyn_array.us) {
			//		resize_allocated(us + dyn_array.us);
			//	}
			//	copy_array(a + us, dyn_array.a, dyn_array.us);
			//	us += dyn_array.us;
			//	return *this;
			//}


			dynamic_stack operator+(const dynamic_stack& dyn_array) {
				dynamic_stack new_array(a, us, dyn_array.us);
				new_array += dyn_array;
				return new_array;
			}
			dynamic_stack operator+(dynamic_stack&& dyn_array) {
				//TODO
				if (dyn_array.as < dyn_array.us + us) {
					T* buffer = malloc_t<T>(dyn_array.us + us);
					copy_array(buffer, a, us);
					copy_array(buffer + us, dyn_array.a, dyn_array.us);
					dyn_array.destruct_array();
					dyn_array.a = buffer;
					dyn_array.us += us;
					return dyn_array;
				}
				else {
					copy_array(dyn_array.a + us, dyn_array.a, dyn_array.us);
					copy_array(dyn_array.a, a, us);
					dyn_array.us += us;
					return dyn_array;
				}
			}
	};
}