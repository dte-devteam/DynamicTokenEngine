#pragma once
namespace dte_token {
	template<typename T>
	struct dynamic_array {
		size_t			as;		//allocated size
		size_t			us;		//used size
		T*				a;		//array
		constexpr dynamic_array() : dynamic_array(nullptr, 0) {}
		template<size_t N>
		constexpr dynamic_array(T (&array)[N]) : dynamic_array(array, N, 0) {}
		constexpr dynamic_array(T* array, size_t use_size) : as(use_size), us(use_size), a(array)  {}
		constexpr dynamic_array(T* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a((T*)malloc(sizeof(T) * as)/*new T[as]*/) {
			T* source = array + us;
			T* target = a + us;
			while (source != array) {
				new (--target) T(*--source);
			}
		}
		constexpr dynamic_array(const dynamic_array<T>& dyn_array, size_t reserve_size = 0) : dynamic_array(dyn_array.a, dyn_array.us, dyn_array.as - dyn_array.us + reserve_size) {}
		constexpr dynamic_array(const dynamic_array<T>& dyn_array, size_t from, size_t to, size_t reserve_size = 0) : dynamic_array(dyn_array.a + std::min(dyn_array.us, from), std::min(dyn_array.us, to) - std::min(dyn_array.us, from), reserve_size) {}
		constexpr ~dynamic_array() {
			//if you got _debugbreak() here - you used wrong constructor:
			//for T array[N] there is dynamic_array(T (&array)[N]) - it will copy it
			//dynamic_array(T* array, size_t use_size) is allowed only for new T[N] - it will hold array by pointer
			//dynamic_array(T* array, size_t use_size) ensures that we won`t make useless duplicate
			T* i = a + us;
			while (i != a) {
				(--i)->~T();
			}
			free(a);
		}
		//for(T t : dyn_array), to do (upgrade?)
		constexpr T* begin() const {
			return a;
		}
		constexpr T* end() const {
			return a + us;
		}
		//--------------------------------------
		template<typename P>
		constexpr T* find(P predicate) const {
			T* i = a + us;
			while (i != a) {
				if (predicate(*--i)) {
					return i;
				}
			}
			return nullptr;
		}
		template<typename P>
		constexpr T* find_ranged(P predicate, size_t from, size_t to) const {
			T* i = a + std::min(us, std::max(from, to));
			T* s = a + std::min(us, from);
			while (i != s) {
				if (predicate(*--i)) {
					return i;
				}
			}
			return nullptr;
		}
		//operators-----------------------------
		constexpr dynamic_array<T>& operator =(const dynamic_array<T>& dyn_array) {
			if (this == &dyn_array) {
				return *this;
			}
			T* target;
			if (as < dyn_array.us) {
				target = a + us;
				while (target != a) {
					(--target)->~T();
				}
				free(a);
				as = dyn_array.as;
				a = (T*)malloc(sizeof(T) * as);
			}
			us = dyn_array.us;
			T* source = dyn_array.a + us;
			target = a + us;
			while (source != dyn_array.a) {
				new (--target) T(*--source);
			}
			return *this;
		}
		constexpr T& operator [](size_t index) const {
			return a[index];
		}
		//--------------------------------------
		constexpr void push_back(const T& element) {
			if (us == as) {
				resize(as + 1);
			}
			a[us] = element;
			++us;
		}
		constexpr void remove(T element) {
			T* i = a + us;
			while (i != a) {
				if (*--i == element) {
					i->~T();
					*i = std::move(a[--us]);
					return;
				}
			}
		}
		constexpr void resize(size_t size) {
			T* new_array = (T*)malloc(sizeof(T) * size);
			as = size;
			us = std::min(as, us);
			T* source = a + us;
			T* target = new_array + us;
			while (source != a) {
				*--target = std::move(*--source);
			}
			free(a);
			a = new_array;
		}
	};
}