#pragma once
#include "dynamic_string.h"
namespace dte_utils {
	//TODO: must be null constructible
	template<dyn_memory_limit T>
	dynamic_string<T>::dynamic_string() : dynamic_string(0) {}
	template<dyn_memory_limit T>
	dynamic_string<T>::dynamic_string(size_t alocate_extra_size) : dynamic_array<T>(alocate_extra_size + 1) {
		this->_push_back(0);
	}

	template<dyn_memory_limit T>
	bool dynamic_string<T>::empty_str() const {
		return !(this->get_used_size() - 1);
	}

	template<dyn_memory_limit T>
	dynamic_string<T>& dynamic_string<T>::operator +=(const dynamic_string& dyn_str) {
		this->provide_array_space(this->get_used_size() + dyn_str.get_used_size() - 1);
		this->pop_back();
		array_to_array(this->end(), dyn_str.begin(), dyn_str.get_used_size());
		this->us += dyn_str.get_used_size();
		if (this == &dyn_str) {
			this->push_back(0);
		}
		return *this;
	}
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_string<T>& dynamic_string<T>::operator +=(const U(&array)[N]) {
		this->provide_array_space(this->get_used_size() + N - 1);
		this->pop_back();
		array_to_array(this->end(), array, N);
		this->us += N;
		return *this;
	}

	template<dyn_memory_limit T>
	dynamic_string<T> dynamic_string<T>::operator+(const dynamic_string& dyn_str) const {
		dynamic_string<T> new_str(this->begin(), this->get_used_size() - 1, dyn_str.get_used_size());
		array_to_array(new_str.end(), dyn_str.begin(), dyn_str.get_used_size());
		new_str.us += dyn_str.get_used_size();
		return new_str;
	}
	template<dyn_memory_limit T>
	dynamic_string<T> dynamic_string<T>::operator+(dynamic_string&& dyn_str) const {
		T* buffer = malloc_t<T>(this->get_used_size() + dyn_str.get_used_size() - 1);
		array_to_array(buffer, this->begin(), this->get_used_size() - 1);
		array_to_array(buffer + this->get_used_size() - 1, dyn_str.begin(), dyn_str.get_used_size());
		dyn_str.destruct_array();
		dyn_str.a = buffer;
		dyn_str.us += this->get_used_size() - 1;
		return dyn_str;
	}

	//should be faster than +dynamic_stack&& because of no reallocation
	template<dyn_memory_limit T>
	template<copyable_or_movable<T> U, size_t N>
	dynamic_string<T> dynamic_string<T>::operator+(const U(&array)[N]) {
		dynamic_string new_str(this->begin(), this->get_used_size() - 1, N);
		array_to_array(new_str.begin() + this->get_used_size() - 1, array, N);
		new_str.us += N;
		return new_str;
	}
}