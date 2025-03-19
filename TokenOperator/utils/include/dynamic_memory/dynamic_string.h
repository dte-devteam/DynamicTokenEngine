#pragma once
#include "dynamic_array.h"
namespace dte_utils {
	template<dyn_memory_limit T>
	struct dynamic_string : public dynamic_array<T> {
		using dynamic_array<T>::dynamic_array;

		dynamic_string();
		dynamic_string(size_t alocate_size);

		bool empty_str() const;

		dynamic_string& operator +=(const dynamic_string& dyn_str);
		template<copyable_or_movable<T> U, size_t N>
		dynamic_string& operator +=(const U(&array)[N]);

		dynamic_string operator+(const dynamic_string& dyn_str) const;
		dynamic_string operator+(dynamic_string&& dyn_str) const;

		//should be faster than +dynamic_stack&& because of no reallocation
		template<copyable_or_movable<T> U, size_t N>
		dynamic_string operator+(const U(&array)[N]);
	};

	using dynamic_cstring = dynamic_string<char>;
	using dynamic_wstring = dynamic_string<wchar_t>;
}