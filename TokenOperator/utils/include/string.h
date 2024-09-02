#pragma once
#include "dynamic_array.h"
namespace dte_utils {
	template<typename T>
	concept null_setable = noexcept(T(0));
	template<null_setable T>
	struct string : public dynamic_array<T> {
		using dynamic_array<T>::dynamic_array;
		string<T>& operator +=(const dynamic_array<T>& str) {
			pop_back();
			provide_subarray_space(str.us);
			T* i = end();
			for (const T& element : str) {
				*i = element;
				++i;
			}
			us += str.us;
			if (this == &str) {
				push_back(0);
			}
			return *this;
		}
		string<T> operator +(const dynamic_array<T>& str) const {
			string<T> result(a, us - 1, str.get_used_size());
			T* i = result.end();
			for (const T& element : str) {
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
			T* i = result.end();
			for (const T& element : str) {
				if constexpr (std::is_trivially_move_constructible_v<T>) {
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
		string<T> operator +(const T(&array)[N]) const {
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
		string<T> operator +(const U(&array)[N]) const {
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
		template<size_t N, null_setable T>
		friend string<T> operator +(const T(&array)[N], const string<T>& str);
	};
	template<size_t N, null_setable T>
	string<T> operator +(const T(&array)[N], const string<T>& str) {
		string<T> result(array, N - 1, str.us);
		T* i = result.end();
		for (const T& element : str) {
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
	template<size_t N, null_setable T>
	string<T> operator +(const T(&array)[N], string<T>&& str) {
		str.insert(0, array, array + N - 1);
		return str;
	}
	typedef string<char> dynamic_string;
	typedef string<wchar_t> dynamic_wstring;
}