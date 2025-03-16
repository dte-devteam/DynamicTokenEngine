#pragma once
#include "dynamic_string.h"
namespace dte_utils {
	template<dyn_memory_limit T>
	dynamic_string<T>& dynamic_string<T>::operator +=(const dynamic_string& dyn_str) {
		pop_back();
		if (as < us + dyn_str.us) {
			resize_allocated(us + dyn_str.us + 1);
		}
		array_to_array(end(), dyn_str.a, dyn_str.us);
		us += dyn_str.us;
		if (this == &dyn_str) {
			push_back(0);
		}
		return *this;
	}
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_string<T>& dynamic_string<T>::operator +=(const U(&array)[N]) {
		pop_back();
		if (as < us + N) {
			resize_allocated(us + N);
		}
		array_to_array(a + us, array, N);
		us += N;
		return *this;
	}

	template<dyn_memory_limit T>
	dynamic_string<T> dynamic_string<T>::operator+(const dynamic_string& dyn_str) const {}
	template<dyn_memory_limit T>
	dynamic_string<T> dynamic_string<T>::operator+(dynamic_string&& dyn_str) const {
		T* buffer = malloc_t<T>(us + dyn_str.us - 1);
		array_to_array(buffer, a, us - 1);
		array_to_array(buffer + us - 1, dyn_str.a, dyn_str.us);
		dyn_str.destruct_array();
		dyn_str.a = buffer;
		dyn_str.us += us - 1;
		return dyn_str;
	}

	//should be faster than +dynamic_stack&& because of no reallocation
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_string<T> dynamic_string<T>::operator+(const U(&array)[N]) {
		dynamic_string new_str(a, us - 1, N);
		array_to_array(new_str.a + us - 1, array, N);
		new_str.us += N;
		return new_str;
	}
}