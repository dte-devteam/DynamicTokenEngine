export module dynamic_string;
import constraints;
import memory;
import dynamic_stack;
import dynamic_array;
export namespace dte_utils {
	template<dyn_memory_limit T> 
	struct dynamic_string : dynamic_array<T> {
		using dynamic_array<T>::dynamic_array;

		dynamic_string() : dynamic_string(0) {}
		dynamic_string(size_t alocate_extra_size) : dynamic_array<T>(alocate_extra_size + 1) {
			this->_push_back(0);
		}

		bool empty_str() const {
			return !(this->get_used_size() - 1);
		}

		dynamic_string& operator +=(const dynamic_string& dyn_str) {
			this->provide_array_space(this->get_used_size() + dyn_str.get_used_size() - 1);
			this->pop_back();
			array_to_array(this->end(), dyn_str.begin(), dyn_str.get_used_size());
			this->us += dyn_str.get_used_size();
			if (this == &dyn_str) {
				this->push_back(0);
			}
			return *this;
		}
		template<copyable_or_movable<T> U, size_t N>
		dynamic_string& operator +=(const U(&array)[N]) {
			this->provide_array_space(this->get_used_size() + N - 1);
			this->pop_back();
			array_to_array(this->end(), array, N);
			this->us += N;
			return *this;
		}

		dynamic_string operator+(const dynamic_string& dyn_str) const {
			dynamic_string<T> new_str(this->begin(), this->get_used_size() - 1, dyn_str.get_used_size());
			array_to_array(new_str.end(), dyn_str.begin(), dyn_str.get_used_size());
			new_str.us += dyn_str.get_used_size();
			return new_str;
		}
		dynamic_string operator+(dynamic_string&& dyn_str) const {
			T* buffer = malloc_t<T>(this->get_used_size() + dyn_str.get_used_size() - 1);
			array_to_array(buffer, this->begin(), this->get_used_size() - 1);
			array_to_array(buffer + this->get_used_size() - 1, dyn_str.begin(), dyn_str.get_used_size());
			dyn_str.destruct_array();
			dyn_str.a = buffer;
			dyn_str.us += this->get_used_size() - 1;
			return dyn_str;
		}

		//should be faster than +dynamic_stack&& because of no reallocation
		template<copyable_or_movable<T> U, size_t N>
		dynamic_string operator+(const U(&array)[N]) {
			dynamic_string new_str(this->begin(), this->get_used_size() - 1, N);
			array_to_array(new_str.begin() + this->get_used_size() - 1, array, N);
			new_str.us += N;
			return new_str;
		}
	};

	using dynamic_cstring = dynamic_string<char>;
	using dynamic_wstring = dynamic_string<wchar_t>;
}