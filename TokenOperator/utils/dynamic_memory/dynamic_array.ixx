module;
#include <malloc.h>
#include <type_traits>
export module utils.dynamic_memory.dynamic_array;
import constraints;
import memory;
import utils.dynamic_memory.dynamic_stack;
export namespace dte_utils {
	template<dyn_memory_limit T>
	struct dynamic_array : dynamic_stack<T> {
		using dynamic_stack<T>::dynamic_stack;
		protected:
			T* new_spased_buffer(size_t new_size, T* gap_pos, size_t gap_size) {
				T* buffer = malloc_t<T>(new_size);
				size_t fisrt_section_size = gap_pos - this->begin();
				array_to_array(buffer, this->begin(), fisrt_section_size);
				array_to_array(
					buffer + fisrt_section_size + gap_size,
					this->begin() + fisrt_section_size,
					this->get_used_size() - fisrt_section_size
				);
				return buffer;
			}
		public:
			template<copy_constructible<T> U>
			void insert(T* pos, const U& value) {
				//TODO: what if T isn`t move assignable
				if (this->get_used_size() == this->get_alloc_size()) {
					T* buffer = new_spased_buffer(++this->as, pos, 1);
					new (buffer + (pos - this->begin())) T(value);
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(this->begin(), this->end());
					}
					free(this->begin());
					++this->us;
					this->a = buffer;
				}
				else {
					T* over_pos = this->end();
					new (over_pos) T(value);
					++this->us;
					while (over_pos != pos) {
						*--over_pos = std::move(*over_pos);
					}
				}
			}
			template<move_constructible<T> U>
			void insert(T* pos, U&& value) {
				//TODO: what if T isn`t move assignable
				if (this->get_used_size() == this->get_alloc_size()) {
					T* buffer = new_spased_buffer(++this->as, pos, 1);
					new (buffer + (pos - this->begin())) T(std::move(value));
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(this->begin(), this->end());
					}
					free(this->begin());
					++this->us;
					this->a = buffer;
				}
				else {
					T* over_pos = this->end();
					new (over_pos) T(std::move(value));
					++this->us;
					while (over_pos != pos) {
						*--over_pos = std::move(*over_pos);
					}
				}
			}
			template<copy_constructible<T> U>
			void insert(T* pos, const U& value, size_t num) {
				//TODO: what if T isn`t move assignable
				if (this->get_alloc_size() < this->get_used_size() + num) {
					T* buffer = new_spased_buffer(this->get_used_size() + num, pos, num);
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(this->begin(), this->end());
					}
					this->us += num;
					size_t delta = pos - this->begin();
					while (num) {
						new (buffer + delta) T(value);
						++delta;
						--num;
					}
					free(this->begin());
					this->a = buffer;
				}
				else {
					this->us += num;
					T* over_pos = this->end();
					size_t _num = num;
					while (_num) {
						new (--over_pos) T(value);
						--_num;
					}
					T* under_pos = this->end() - num;
					while (num) {
						over_pos = under_pos;
						while (over_pos != pos) {
							*--over_pos = std::move(*over_pos);
						}
						++under_pos;
						++pos;
						--num;
					}
				}
			}
			template<copy_constructible<T> U>
			void insert(T* pos, const U* first, const U* last) {
				//TODO: what if T isn`t move assignable
				size_t num = last - first;
				if (this->get_alloc_size() < this->get_used_size() + num) {
					T* buffer = new_spased_buffer(this->us + num, pos, num);
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(this->begin(), this->end());
					}
					this->us += num;
					size_t delta = pos - this->begin();
					while (first != last) {
						new (buffer + delta) T(*first);
						++delta;
						++first;
					}
					free(this->begin());
					this->a = buffer;
				}
				else {
					this->us += num;
					T* over_pos = this->end();
					while (first != last) {
						new (--over_pos) T(*--last);
					}
					T* under_pos = this->end() - num;
					while (num) {
						over_pos = under_pos;
						while (over_pos != pos) {
							*--over_pos = std::move(*over_pos);
						}
						++under_pos;
						++pos;
						--num;
					}
				}
			}
			template<copy_constructible<T> U>
			void insert(T* pos, std::initializer_list<U> il) {
				insert(pos, il.begin(), il.end());
			}

			template<typename ...Args>
			void emplace(T* pos, Args&&... args) requires std::is_constructible_v<T, Args&&...> {
				//TODO: what if T isn`t move assignable
				if (this->get_used_size() == this->get_alloc_size()) {
					T* buffer = new_spased_buffer(++this->as, pos, 1);
					new (buffer + (pos - this->begin())) T(std::forward<Args>(args)...);
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(this->begin(), this->end());
					}
					free(this->begin());
					++this->us;
					this->a = buffer;
				}
				else {
					T* over_pos = this->end();
					new (over_pos) T(std::forward<Args>(args)...);
					++this->us;
					while (over_pos != pos) {
						*--over_pos = std::move(*over_pos);
					}
				}
			}

			void erase(T* pos) {
				//TODO: what if T isn`t move assignable
				T* over_pos = pos + 1;
				while (over_pos != this->end()) {
					*pos = std::move(*over_pos);
					++pos;
					++over_pos;
				}
				if constexpr (!std::is_trivially_destructible_v<T>) {
					this->a[--this->us].~T();
				}
				else {
					--this->us;
				}
			}
			void erase(T* first, T* last) {
				//TODO: what if T isn`t move assignable
				size_t size = last - first;
				while (last != this->end()) {
					*first = std::move(*last);
					++first;
					++last;
				}
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(this->end() - size, this->end());
				}
				this->us -= size;
			}

			//unordered removal (faster, but order breaks)
			void remove(T* pos) {
				if (pos + 1 == this->end()) {
					this->pop_back();
				}
				else {
					if constexpr (std::is_move_assignable_v<T>) {
						*pos = std::move(this->a[--this->us]);
					}
					else {
						*pos = this->a[--this->us];
					}
					if constexpr (!std::is_trivially_destructible_v<T>) {
						this->a[this->get_used_size()].~T();
					}
				}
			}
			//is effective in larger arrays and smaller removal
			void remove(T* first, T* last) {
				if (last == this->end()) {
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(first, this->end());
					}
					this->us -= last - first;
				}
				else {
					T* over_pos = this->end();
					this->us -= last - first;
					while (last != first) {
						*--last = std::move(*--over_pos);
						over_pos->~T();
					}
				}
			}
	};
}