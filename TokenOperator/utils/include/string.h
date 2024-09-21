#pragma once
#include "dynamic_array.h"
namespace dte_utils {
	template<typename T>
	concept null_setable = noexcept(T(0));
	template<null_setable T>
	struct string : dynamic_array<T> {
		template<null_setable U> friend struct string;
		using dynamic_array<T>::dynamic_array;
		string<T>& operator +=(const dynamic_array<T>& str) {
			provide_subarray_space(str.get_used_size());
			pop_back();
			T* i = end();
			for (const T& element : str) {
				push_back(element);
			}
			us += str.get_used_size();
			if (this == &str) {
				push_back(0);
			}
			return *this;
		}
		string<T> operator +(const dynamic_array<T>& str) const {
			string<T> result(a, us - 1, str.get_used_size());
			T* i = result.end();
			for (const T& element : str) {
				result.push_back(element);
			}
			result.us = result.as;
			return result;
		}
		template<null_setable U>
		string<T> operator +(const dynamic_array<U>& str) const {
			string<T> result(a, us - 1, str.get_used_size());
			T* i = result.end();
			for (const U& element : str) {
				if constexpr (std::is_trivially_constructible_v<T, const U&>) {
					*i = element;
				}
				else {
					new (i) T(element);
				}
				++i;
			}
			result.us = result.as;
			return result;
		}
		string<T> operator +(dynamic_array<T>&& str) const {
			string<T> result(a, us - 1, str.get_used_size());
			for (const T& element : str) {
				result.push_back(std::move(element));
			}
			return result;
		}
		template<null_setable U>
		string<T> operator +(dynamic_array<U>&& str) const {
			string<T> result(a, us - 1, str.get_used_size());
			T* i = result.end();
			for (const U& element : str) {
				if constexpr (std::is_trivially_constructible_v<T, U&&>) {
					*i = std::move(element);
				}
				else {
					new (i) T(std::move(element));
				}
				++i;
			}
			result.us = result.as;
			return result;
		}
		template<size_t N>
		string<T> operator +(const T (&array)[N]) const {
			string<T> result(a, us - 1, N);
			T* i = result.end();
			for (const T& element : array) {
				if constexpr (std::is_trivially_copy_constructible_v<T>) {
					*i = element;
				}
				else {
					new (i) T(element);
				}
				++i;
			}
			result.us = result.as;
			return result;
		}
		template<size_t N, null_setable U>
		string<T> operator +(const U (&array)[N]) const {
			string<T> result(a, us - 1, N);
			T* i = result.end();
			for (const U& element : array) {
				if constexpr (std::is_trivially_constructible_v<T, const U&>) {
					*i = element;
				}
				else {
					new (i) T(element);
				}
				++i;
			}
			result.us = result.as;
			return result;
		}
	};
	template<size_t N, null_setable T, null_setable U>
	string<T> operator +(const U (&array)[N], const string<T>& str) {
		string<T> result(array, N - 1, str.get_used_size());
		for (const T& element : str) {
			result.push_back(element);
		}
		return result;
	}
	template<size_t N, null_setable T, null_setable U>
	string<T> operator +(const U (&array)[N], string<T>&& str) {
		str.insert(0, array, array + N - 1);
		return str;
	}
	typedef string<char> dynamic_string;
	typedef string<wchar_t> dynamic_wstring;
}