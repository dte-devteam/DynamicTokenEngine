#pragma once
#include <iostream>
namespace dte_utils {
	template<typename T>
	struct dynamic_array {
		template <typename U> friend struct dynamic_array;
		protected:
			size_t			as;		//allocated size
			size_t			us;		//used size
			T*				a;		//array
			void move_subarray_right(T* pos, size_t shift) {
				T* s = end();
				T* t = s + shift;
				while (s != pos) {
					*--t = std::move(*--s);
				}
			}
			void move_subarray_left(T* pos, size_t shift) {
				while (pos != end()) {
					*(pos - shift) = std::move(*pos);
					++pos;
				}
			}
			bool pointer_out_of_array(const T* pointer) const {
				return pointer < a || pointer > back();
			}
			void validate_pointer(T* old_begin, const T*& pointer, size_t movement) const {
				if (!pointer_out_of_array(pointer)) {
					pointer += a - old_begin + movement;
				}
			}
		public:
			dynamic_array() : dynamic_array(nullptr, 0) {}
			template<size_t N>
			dynamic_array(T (&array)[N]) : dynamic_array(array, N, 0) {}
			dynamic_array(T* array, size_t use_size) : as(use_size), us(use_size), a(array)  {}
			dynamic_array(T* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a((T*)malloc(sizeof(T) * as)) {
				T* source = array + us;
				T* target = end();
				while (source != array) {
					new (--target) T(*--source);
				}
			}
			dynamic_array(const dynamic_array<T>& dyn_array) : dynamic_array(dyn_array.a, dyn_array.us, 0) {}
			dynamic_array(const dynamic_array<T>& dyn_array, size_t reserve_size) : dynamic_array(dyn_array.a, dyn_array.us, dyn_array.as - dyn_array.us + reserve_size) {}
			dynamic_array(const dynamic_array<T>& dyn_array, size_t from, size_t to, size_t reserve_size = 0) : dynamic_array(dyn_array.a + from, to - from, reserve_size) {
				#ifdef DA_DEBUG
					//to do (to > from || to > dyn_array.us) -> error
				#endif
			}
			dynamic_array(dynamic_array<T>&& dyn_array) noexcept : as(std::move(dyn_array.as)), us(std::move(dyn_array.us)), a(std::move(dyn_array.a)) {}
			template<size_t N, typename U>
			dynamic_array(U (&init_array)[N]) : dynamic_array(init_array, N){}
			template<typename U>
			dynamic_array(U* init_array, size_t use_size, size_t reserve_size = 0) : as(use_size + reserve_size), us(use_size), a((T*)malloc(sizeof(T) * as)) {
				U* source = init_array + us;
				T* target = end();
				while (source != init_array) {
					new (--target) T(*--source);
				}
			}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array) : dynamic_array(dyn_array.a, dyn_array.us, 0) {}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array, size_t reserve_size) : dynamic_array(dyn_array.a, dyn_array.us, dyn_array.as - dyn_array.us + reserve_size) {}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array, size_t from, size_t to, size_t reserve_size = 0) : dynamic_array(dyn_array.a + from, to - from, reserve_size) {
				#ifdef DA_DEBUG
					//to do (to > from || to > dyn_array.us) -> error
				#endif
			}
			~dynamic_array() {
				//if you got _debugbreak() here - you used wrong constructor:
				//for T/U array[N] there is dynamic_array(T/U (&array)[N]) - it will copy it
				//dynamic_array(T/U* array, size_t use_size) is allowed only for new T/U[N] - it will hold array by pointer
				//dynamic_array(T/U* array, size_t use_size) ensures that we won`t make useless duplicate
				T* i = end();
				while (i != a) {
					(--i)->~T();
				}
				free(a);
			}
			//for(T t : dyn_array), to do (upgrade?)
			T* begin() const {
				return a;
			}
			T* end() const {
				return a + us;
			}
			T* back() const {
				return us ? end() - 1 : nullptr;
			}
			//--------------------------------------
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
				#ifdef DA_DEBUG
					//to do (to > from || to > us) -> error
				#endif
				T* i = a + to;
				T* s = a + from;
				while (i != s) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			//operators-----------------------------
			dynamic_array<T>& operator =(const dynamic_array<T>& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				T* target;
				if (as < dyn_array.us) {
					target = end();
					while (target != a) {
						(--target)->~T();
					}
					free(a);
					as = dyn_array.as;
					a = (T*)malloc(sizeof(T) * as);
				}
				us = dyn_array.us;
				T* source = dyn_array.end();
				target = end();
				while (source != dyn_array.a) {
					new (--target) T(*--source);
				}
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator =(const dynamic_array<U>& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				T* target;
				if (as < dyn_array.us) {
					target = end();
					while (target != a) {
						(--target)->~T();
					}
					free(a);
					as = dyn_array.as;
					a = (T*)malloc(sizeof(T) * as);
				}
				us = dyn_array.us;
				T* source = dyn_array.end();
				target = end();
				while (source != dyn_array.a) {
					new (--target) T(*--source);
				}
				return *this;
			}
			dynamic_array<T>& operator =(dynamic_array<T>&& dyn_array) noexcept {
				if (this == &dyn_array) {
					return *this;
				}
				free(a);
				as = std::move(dyn_array.as);
				us = std::move(dyn_array.us);
				a = std::move(dyn_array.a);
				return *this;
			}
			T& operator [](size_t index) {
				return a[index];
			}
			const T& operator [](size_t index) const {
				return a[index];
			}
			//move related functions
			void swap(dynamic_array<T>& dyn_array) noexcept {
				std::swap(as, dyn_array.as);
				std::swap(us, dyn_array.us);
				std::swap(a, dyn_array.a);
			}
			//size control--------------------------
			void resize(size_t size) {
				if (size < us) {
					T* i = end();
					us = as = size;
					T* e = end();
					while (i != e) {
						(--i)->~T();
					}
					a = (T*)realloc(a, sizeof(T) * size);
					return;
				}
				T* new_array = (T*)realloc(a, sizeof(T) * size);
				if (new_array) {
					as = size;
					a = new_array;
				}
			}
			void provide_element_space() {
				if (us == as) {
					resize(as + 1);
				}
			}
			void provide_subarray_space(size_t size) {
				if (us + size > as) {
					resize(us + size);
				}
			}
			//--------------------------------------
			void push_back(const T& element) {
				provide_element_space();
				a[us] = element;
				++us;
			}
			void push_back(T&& element) {
				emplace_back(std::move(element));
			}
			template<typename ...Args>
			void emplace_back(Args&&... args) {
				provide_element_space();
				a[us] = { args... };
				++us;
			}
			void pop_back() {
				if (us) {
					a[--us].~T();
				}
			}
			template<typename ...Args>
			void emplace(size_t index, Args&&... args) {
				if (index < us) {
					provide_element_space();
					move_subarray_right(begin() + index, 1);
					*(begin() + index) = {args...};
					++us;
				}
				else {
					emplace_back(args...);
				}
			}
			void insert(size_t index, const T& element) {
				if (index < us) {
					T* old_begin = a;
					const T* p = &element;
					provide_element_space();
					validate_pointer(old_begin, p, p > old_begin + index - 1 ? 1 : 0);
					move_subarray_right(begin() + index, 1);
					*(begin() + index) = *p;
					++us;
				}
				else {
					push_back(element);
				}
			}
			void insert(size_t index, const T& element, size_t count) {
				#ifdef DA_DEBUG
					//to do
				#endif
				if (count) {
					T* old_begin = a;
					const T* p = &element;
					provide_subarray_space(count);
					validate_pointer(old_begin, p, p > old_begin + index - 1 ? count : 0);
					if (index < us) {
						T* i = begin() + index;
						move_subarray_right(i, count);
						us += count;
						i += count;
						while (count) {
							*--i = *p;
							--count;
						}
					}
					else {
						while (count) {
							a[us] = *p;
							++us;
							--count;
						}
					}
				}
			}
			void insert(size_t index, T&& element) {
				//need pointer validation?
				emplace(index, std::move(element));
			}
			void insert(size_t index, const T* first, const T* last) {
				#ifdef DA_DEBUG
					//to do
				#endif
				size_t count = last - first;
				if (count) {
					T* old_begin = a;
					provide_subarray_space(count);
					validate_pointer(old_begin, first, 0);
					validate_pointer(old_begin, last, old_begin + index < last ? 0 : count);
					if (index < us) {
						T* i = begin() + index;
						move_subarray_right(i, count);
						i += count;
						if (last - first != count) {
							//we need to iter: first -> beging() + index & beging() + index + count -> last
							T* s = i;
							while (s != last) {
								*--i = *--last;
							}
							s = begin() + index;
							while (s != first) {
								*--i = *--s;
							}
						}
						else {
							while (first != last) {
								*--i = *--last;
							}
						}
						us += count;
					}
					else {
						while (first != last) {
							a[us] = *--last;
							++us;
						}
					}
				}
			}
			//erase from array - slow and save order
			void erase(T* pos) {
				#ifdef DA_DEBUG
					//to do
				#endif
				if (pos < back()) {
					move_subarray_left(++pos, 1);
					--us;
				}
				else {
					pop_back();
				}
			}
			void erase(T* first, T* last) {
				#ifdef DA_DEBUG
					//to do
				#endif
				if (last == end()) {
					us -= last - first;
					while (last != first) {
						(--last)->~T();
					}
				}
				else {
					us -= last - first;
					move_subarray_left(last, last - first);
				}
			}
			//remove from array - fast and may unsort
			void remove(T* pos) {
				#ifdef DA_DEBUG
					//to do
				#endif
				pos->~T();
				if (pos - a != --us) {
					*pos = std::move(a[us]);
				}
			}
			void remove(T* first, T* last) {
				#ifdef DA_DEBUG
					//to do
				#endif
				while (first != last) {
					remove(--last);
				}
			}
			void clear() {
				T* i = end();
				us = 0;
				while (i != a) {
					(--i)->~T();
				}
				a = nullptr;
			}
			//get methods
			size_t get_used_size() const {
				return us;
			}
			size_t get_allocated_size() const {
				return as;
			}
	};
}