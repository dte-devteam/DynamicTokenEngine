#pragma once
#include "dynamic_stack.h"
namespace dte_utils {
	template<dyn_memory_limit T>
	void dynamic_stack<T>::destruct_array() {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			destruct_range(begin(), end());
		}
		free(a);
	}
	template<dyn_memory_limit T>
	void dynamic_stack<T>::provide_element_space() {
		if (as == us) {
			resize_allocated(as * 2 + 1);
		}
	}
	template<dyn_memory_limit T>
	void dynamic_stack<T>::provide_array_space(size_t required_size) {
		if (get_alloc_size() < required_size) {
			resize_allocated(required_size);
		}
	}

	template<dyn_memory_limit T>
	template<copy_constructible<T> U>
	void dynamic_stack<T>::_push_back(const U& value) {
		if constexpr (std::is_trivially_constructible_v<T, const U&>) {
			a[us] = static_cast<T>(value);
		}
		else {
			new (end()) T(static_cast<T>(value));
		}
		++us;
	}
	template<dyn_memory_limit T>
	template<move_constructible<T> U>
	void dynamic_stack<T>::_push_back(U&& value) {
		if constexpr (std::is_trivially_constructible_v<T, U&&>) {
			a[us] = static_cast<T&&>(value);
		}
		else {
			new (end()) T(static_cast<T&&>(value));
		}
		++us;
	}
	template<dyn_memory_limit T>
	template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
	void dynamic_stack<T>::_emplace_back(Args&&... args) {
		new (end()) T(std::forward<Args>(args)...);
		++us;
	}

	template<dyn_memory_limit T>
	dynamic_stack<T>::dynamic_stack() : us(0), as(0), a(nullptr) {}
	template<dyn_memory_limit T>
	dynamic_stack<T>::dynamic_stack(size_t alocate_size) : us(0), as(alocate_size), a(as ? malloc_t<T>(as) : nullptr) {}
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_stack<T>::dynamic_stack(const U(&array)[N], size_t reserved_size) : dynamic_stack(array, N, reserved_size) {}
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U>
	dynamic_stack<T>::dynamic_stack(const U* array, size_t used_size, size_t reserved_size) : us(used_size), as(us + reserved_size), a(malloc_t<T>(as)) {
		array_to_array(begin(), array, get_used_size());
	}

	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U>
	dynamic_stack<T>::dynamic_stack(std::initializer_list<U> il, size_t reserved_size) : dynamic_stack(il.begin(), il.size(), reserved_size) {}

	template<dyn_memory_limit T>
	dynamic_stack<T>::dynamic_stack(const dynamic_stack& dyn_array) : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(as ? malloc_t<T>(as) : nullptr) {
		array_to_array(begin(), dyn_array.begin(), get_used_size());
	}
	template<dyn_memory_limit T>
	dynamic_stack<T>::dynamic_stack(dynamic_stack&& dyn_array) noexcept : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(dyn_array.begin()) {
		dyn_array.us = 0;
		dyn_array.a = nullptr;
	}

	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U>
	dynamic_stack<T>::dynamic_stack(const dynamic_stack<U>& dyn_array) : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(as ? malloc_t<T>(as) : nullptr) {
		array_to_array(begin(), dyn_array.begin(), get_used_size());
	}

	template<dyn_memory_limit T>
	dynamic_stack<T>::~dynamic_stack() {
		destruct_array();
	}

	template<dyn_memory_limit T>
	T* dynamic_stack<T>::begin() {
		return a;
	}
	template<dyn_memory_limit T>
	const T* dynamic_stack<T>::begin() const {
		return a;
	}
	template<dyn_memory_limit T>
	T* dynamic_stack<T>::end() {
		return a + us;
	}
	template<dyn_memory_limit T>
	const T* dynamic_stack<T>::end() const {
		return a + us;
	}
	
	template<dyn_memory_limit T>
	template<typename P>
	T* dynamic_stack<T>::find(P predicate) {
		T* i = end();
		while (i != a) {
			if (predicate(*--i)) {
				return i;
			}
		}
		return nullptr;
	}
	template<dyn_memory_limit T>
	template<typename P>
	const T* dynamic_stack<T>::find(P predicate) const {
		T* i = end();
		while (i != a) {
			if (predicate(*--i)) {
				return i;
			}
		}
		return nullptr;
	}
	template<dyn_memory_limit T>
	template<typename P>
	T* dynamic_stack<T>::find_ranged(P predicate, size_t from, size_t to) {
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
	template<dyn_memory_limit T>
	template<typename P>
	const T* dynamic_stack<T>::find_ranged(P predicate, size_t from, size_t to) const {
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

	template<dyn_memory_limit T>
	size_t dynamic_stack<T>::get_alloc_size() const {
		return as;
	}
	template<dyn_memory_limit T>
	size_t dynamic_stack<T>::get_used_size() const {
		return us;
	}

	template<dyn_memory_limit T>
	void dynamic_stack<T>::resize_allocated(size_t size) {
		if (!size) {
			destruct_array();
			us = as = 0;
			a = nullptr;
			return;
		}
		if (get_used_size() > size) {
			if constexpr (!std::is_trivially_destructible_v<T>) {
				destruct_range(begin() + size, end());
			}
			us = size;
		}
		if (as != size) {
			if constexpr (std::is_trivially_move_constructible_v<T>) {
				a = realloc_t(begin(), size);
			}
			else {
				T* buffer = malloc_t<T>(size);
				array_to_array(buffer, begin(), get_used_size());
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(begin(), end());
				}
				free(begin());
				a = buffer;
			}
			as = size;
		}
	}
	template<dyn_memory_limit T>
	void dynamic_stack<T>::clear() {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			destruct_range(begin(), end());
		}
		us = 0;
	}

	template<dyn_memory_limit T>
	template<copy_constructible<T> U>
	void dynamic_stack<T>::push_back(const U& value) {
		provide_element_space();
		_push_back(value);
	}
	template<dyn_memory_limit T>
	template<move_constructible<T> U>
	void dynamic_stack<T>::push_back(U&& value) {
		provide_element_space();
		_push_back(value);
	}
	template<dyn_memory_limit T>
	template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
	void dynamic_stack<T>::emplace_back(Args&&... args) {
		provide_element_space();
		_emplace_back(args...);
	}
	template<dyn_memory_limit T>
	void dynamic_stack<T>::pop_back() {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			a[--us].~T();
		}
		else {
			--us;
		}
	}
	
	template<dyn_memory_limit T>
	dynamic_stack<T>& dynamic_stack<T>::operator =(const dynamic_stack& dyn_array) {
		if (this == &dyn_array) {
			return *this;
		}
		destruct_array();
		us = dyn_array.get_used_size();
		as = dyn_array.get_alloc_size();
		a = malloc_t<T>(get_alloc_size());
		array_to_array(begin(), dyn_array.begin(), get_used_size());
		return *this;
	}
	template<dyn_memory_limit T>
	dynamic_stack<T>& dynamic_stack<T>::operator =(dynamic_stack&& dyn_array) noexcept {
		if (this == &dyn_array) {
			return *this;
		}
		std::swap(a, dyn_array.a);
		std::swap(as, dyn_array.as);
		std::swap(us, dyn_array.us);
		return *this;
	}
	template<dyn_memory_limit T>
	dynamic_stack<T>& dynamic_stack<T>::operator +=(const dynamic_stack& dyn_array) {
		provide_array_space(get_used_size() + dyn_array.get_used_size());
		array_to_array(end(), dyn_array.get_alloc_size(), dyn_array.get_used_size());
		us += dyn_array.get_used_size();
		return *this;
	}
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_stack<T>& dynamic_stack<T>::operator +=(const U(&array)[N]) {
		provide_array_space(get_used_size() + N);
		array_to_array(end(), array, N);
		us += N;
		return *this;
	}

	template<dyn_memory_limit T>
	dynamic_stack<T> dynamic_stack<T>::operator+(const dynamic_stack& dyn_array) const {
		dynamic_stack<T> new_array(begin(), get_used_size(), dyn_array.get_used_size());
		new_array += dyn_array;
		return new_array;
	}
	template<dyn_memory_limit T>
	dynamic_stack<T> dynamic_stack<T>::operator+(dynamic_stack&& dyn_array) const {
		if (dyn_array.get_alloc_size() < dyn_array.get_used_size() + get_used_size()) {
			T* buffer = malloc_t<T>(dyn_array.get_used_size() + get_used_size());
			array_to_array(buffer, begin(), get_used_size());
			array_to_array(buffer + get_used_size(), dyn_array.begin(), dyn_array.get_used_size());
			dyn_array.destruct_array();
			dyn_array.a = buffer;
			dyn_array.us += get_used_size();
			return dyn_array;
		}
		else {
			array_to_array(dyn_array.begin() + get_used_size(), dyn_array.begin(), dyn_array.get_used_size());
			array_to_array(dyn_array.begin(), begin(), get_used_size());
			dyn_array.us += us;
			return dyn_array;
		}
	}

	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_stack<T> dynamic_stack<T>::operator+(const U(&array)[N]) {
		dynamic_stack new_array(begin(), get_used_size(), N);
		array_to_array(new_array.end(), array, N);
		new_array.us += N;
		return new_array;
	}
}