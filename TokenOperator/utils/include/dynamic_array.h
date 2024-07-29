#pragma once
#include <new>	//to do - find out why fixes error C2661 with operator new
#include <type_traits>
namespace dte_utils {
	//to do: handle malloc(N) = NULL (memory shortage) 
	template<typename T>
	struct dynamic_array {
		template<typename U> friend struct dynamic_array;
		protected:
			size_t			as;		//allocated size
			size_t			us;		//used size
			T*				a;		//array
			void move_subarray_right(T* pos, size_t shift) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>
			){
				T* source = end();
				T* target = source + shift;
				while (source != pos) {
					*--target = std::move(*--source);
				}
			}
			void move_subarray_left(T* pos, size_t shift) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>
			){
				while (pos != end()) {
					*(pos - shift) = std::move(*pos);
					++pos;
				}
			}
			bool pointer_out_of_array(const T* pointer) const noexcept {
				return pointer < a || pointer > back();
			}
			void validate_pointer(T* old_begin, const T*& pointer, size_t movement) const noexcept {
				if (!pointer_out_of_array(pointer)) {
					pointer += a - old_begin + movement;
				}
			}
		public:
			dynamic_array() : dynamic_array(nullptr, 0) {}
			template<size_t N>
			dynamic_array(T (&array)[N]) : dynamic_array(array, N, 0) {}
			dynamic_array(T* array, size_t use_size) : as(use_size), us(use_size), a(array)  {}
			dynamic_array(T* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a(static_cast<T*>(malloc(sizeof(T) * as))) {
				T* source = array + us;
				T* target = end();
				while (source != array) {
					if constexpr (std::is_trivially_copy_constructible_v<T>) {
						*--target = *--source;
					}
					else {
						new (--target) T(*--source);
					}
				}
			}
			dynamic_array(const dynamic_array<T>& dyn_array) : dynamic_array(dyn_array.a, dyn_array.us, 0) {}
			dynamic_array(const dynamic_array<T>& dyn_array, size_t reserve_size) : dynamic_array(dyn_array.a, dyn_array.us, reserve_size) {}
			dynamic_array(const dynamic_array<T>& dyn_array, size_t from, size_t to, size_t reserve_size) : dynamic_array(dyn_array.a + from, to - from, reserve_size) {
				#ifdef DA_DEBUG
					//to do (to > from || to > dyn_array.us) -> error
				#endif
			}
			dynamic_array(dynamic_array<T>&& dyn_array) noexcept : as(std::move(dyn_array.as)), us(std::move(dyn_array.us)), a(std::move(dyn_array.a)) {}
			template<size_t N, typename U>
			dynamic_array(U (&array)[N]) : dynamic_array(array, N){}
			template<typename U>
			dynamic_array(U* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a(static_cast<T*>(malloc(sizeof(T) * as))) {
				U* source = array + us;
				T* target = end();
				while (source != array) {
					if constexpr (std::is_trivially_constructible_v<T, const U&>) {
						*--target = *--source;
					}
					else {
						new (--target) T(*--source);
					}
				}
			}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array) : dynamic_array(dyn_array.a, dyn_array.us, 0) {}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array, size_t reserve_size) : dynamic_array(dyn_array.a, dyn_array.us, reserve_size) {}
			template<typename U>
			dynamic_array(const dynamic_array<U>& dyn_array, size_t from, size_t to, size_t reserve_size) : dynamic_array(dyn_array.a + from, to - from, reserve_size) {
				#ifdef DA_DEBUG
					//to do (to > from || to > dyn_array.us) -> error
				#endif
			}
			template<typename U>
			dynamic_array(dynamic_array<U>&& dyn_array) noexcept : as(std::move(dyn_array.as)), us(std::move(dyn_array.us)), a(static_cast<T*>(malloc(sizeof(T)* as))) {
				U* source = dyn_array.a + us;
				T* target = end();
				while (source != dyn_array.a) {
					if constexpr (std::is_trivially_constructible_v<T, U&&>) {
						*--target = std::move(*--source);
					}
					else {
						new (--target) T(std::move(*--source));
					}
				}
			}
			~dynamic_array() {
				//if you got _debugbreak() here - you used wrong constructor:
				//for T/U array[N] there is dynamic_array(T/U (&array)[N]) - it will copy it
				//dynamic_array(T/U* array, size_t use_size) is allowed only for new T/U[N] - it will hold array by pointer
				//dynamic_array(T/U* array, size_t use_size) ensures that we won`t make useless duplicate
				if constexpr (!std::is_trivially_destructible_v<T>) {
					T* i = end();
					while (i != a) {
						(--i)->~T();
					}
				}
				free(a);
			}
			//for(T t : dyn_array), to do (upgrade?)
			T* begin() const noexcept {
				return a;
			}
			T* end() const noexcept {
				return a + us;
			}
			T* back() const noexcept {
				return us ? end() - 1 : nullptr;
			}
			//--------------------------------------
			template<typename P>
			T* find(P predicate) const noexcept(
				noexcept(predicate(std::declval<T>()))
			){
				T* i = end();
				while (i != a) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			template<typename P>
			T* find_ranged(P predicate, size_t from, size_t to) const noexcept(
				noexcept(predicate(std::declval<T>()))
			){
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
					if constexpr (!std::is_trivially_destructible_v<T>) {
						target = end();
						while (target != a) {
							(--target)->~T();
						}
					}
					free(a);
					as = dyn_array.as;
					a = static_cast<T*>(malloc(sizeof(T) * as));
				}
				us = dyn_array.us;
				T* source = dyn_array.end();
				target = end();
				while (source != dyn_array.a) {
					if constexpr (std::is_trivially_copy_constructible_v<T>) {
						*--target = *--source;
					}
					else {
						new (--target) T(*--source);
					}
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
					if constexpr (!std::is_trivially_destructible_v<T>) {
						target = end();
						while (target != a) {
							(--target)->~T();
						}
					}
					free(a);
					as = dyn_array.as;
					a = static_cast<T*>(malloc(sizeof(T) * as));
				}
				us = dyn_array.us;
				U* source = dyn_array.end();
				target = end();
				while (source != dyn_array.a) {
					if constexpr (std::is_trivially_constructible_v<T, const U&>) {
						*--target = *--source;
					}
					else {
						new (--target) T(*--source);
					}
				}
				return *this;
			}
			dynamic_array<T>& operator =(dynamic_array<T>&& dyn_array) noexcept {
				if (this == &dyn_array) {
					return *this;
				}
				if constexpr (!std::is_trivially_destructible_v<T>) {
					T* target = end();
					while (target != a) {
						(--target)->~T();
					}
				}
				free(a);
				dynamic_array<T>(std::move(dyn_array));
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator =(dynamic_array<U>&& dyn_array) noexcept {
				if (this == &dyn_array) {
					return *this;
				}
				if constexpr (!std::is_trivially_destructible_v<T>) {
					T* target = end();
					while (target != a) {
						(--target)->~T();
					}
				}
				free(a);
				dynamic_array(std::move(dyn_array));
				return *this;
			}
			dynamic_array<T>& operator +=(const dynamic_array<T>& dyn_array) {
				provide_subarray_space(dyn_array.us);
				T* i = end();
				for (const T& element : dyn_array) {
					if constexpr (std::is_trivially_copy_constructible_v<T>) {
						*i = element;
					}
					else {
						new (i) T(element);
					}
					++i;
				}
				us += dyn_array.us;
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator +=(const dynamic_array<U>& dyn_array) {
				provide_subarray_space(dyn_array.us);
				T* i = end();
				for (const U& element : dyn_array) {
					if constexpr (std::is_trivially_constructible_v<T, const U&>) {
						*i = element;
					}
					else {
						new (i) T(element);
					}
					++i;
				}
				us += dyn_array.us;
				return *this;
			}
			dynamic_array<T>& operator +=(dynamic_array<T>&& dyn_array) noexcept {
				provide_subarray_space(dyn_array.us);
				T* source = dyn_array.end();
				T* target = back() + dyn_array.us;
				while (source != dyn_array.a) {
					if constexpr (std::is_trivially_move_constructible_v<T>) {
						*--target = std::move(*--source);
					}
					else {
						new (--target) T(std::move(*--source));
					}
				}
				us += dyn_array.us;
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator +=(dynamic_array<U>&& dyn_array) noexcept {
				provide_subarray_space(dyn_array.us);
				U* source = dyn_array.end();
				T* target = back() + dyn_array.us;
				while (source != dyn_array.a) {
					if constexpr (std::is_trivially_constructible_v<T, U&&>) {
						*--target = std::move(*--source);
					}
					else {
						new (--target) T(std::move(*--source));
					}
				}
				us += dyn_array.us;
				return *this;
			}
			T& operator [](size_t index) {
				#ifdef DA_DEBUG
					//to do (index > us - 1) -> error
				#endif
				return a[index];
			}
			const T& operator [](size_t index) const {
				#ifdef DA_DEBUG
					//to do (index > us - 1) -> error
				#endif
				return a[index];
			}
			bool operator ==(const dynamic_array<T>& dyn_array) const noexcept(
				noexcept(std::declval<T>() != std::declval<T>())
			){
				if (us == dyn_array.us) {
					T* this_i = a;
					for (T& i : dyn_array) {
						if (*this_i != i) {
							return false;
						}
						++this_i;
					}
					return true;
				}
				return false;
			}
			bool operator !=(const dynamic_array<T>& dyn_array) const noexcept(
				noexcept(std::declval<T>() != std::declval<T>())
			){
				return !(*this == dyn_array);
			}
			//move related functions
			void swap(dynamic_array<T>& dyn_array) noexcept {
				std::swap(as, dyn_array.as);
				std::swap(us, dyn_array.us);
				std::swap(a, dyn_array.a);
			}
			//size control--------------------------
			void resize(size_t size) noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (size < us) {
					if constexpr (!std::is_trivially_destructible_v<T>) {
						T* i = end();
						us = as = size;
						T* e = end();
						while (i != e) {
							(--i)->~T();
						}
					}
					a = static_cast<T*>(realloc(a, sizeof(T) * size));
					return;
				}
				T* new_array = static_cast<T*>(realloc(a, sizeof(T) * size));
				if (new_array) {
					as = size;
					a = new_array;
				}
			}
			void provide_element_space() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (us == as) {
					resize(as + 1);
				}
			}
			void provide_subarray_space(size_t size) noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (us + size > as) {
					resize(us + size);
				}
			}
			//--------------------------------------
			void push_back(const T& element) noexcept(
				std::is_nothrow_destructible_v<T>&&
				std::is_trivially_copy_constructible_v<T> ? std::is_nothrow_assignable_v<T&, const T&> : std::is_nothrow_copy_constructible_v<T>
			){
				provide_element_space();
				if constexpr (std::is_trivially_copy_constructible_v<T>) {
					a[us] = element;
				}
				else {
					new (a + us) T(element);
				}
				++us;
			}
			void push_back(T&& element) noexcept(
				std::is_nothrow_constructible_v<T, T&&>&&
				std::is_nothrow_destructible_v<T>
			){
				emplace_back(std::move(element));
			}
			template<typename ...Args>
			void emplace_back(Args&&... args) noexcept(
				std::is_nothrow_constructible_v<T, Args&&...>&&
				std::is_nothrow_destructible_v<T>
			){
				provide_element_space();
				if constexpr (std::is_trivially_constructible_v<T, Args&&...>) {
					a[us] = { args... };
				}
				else {
					new (a + us) T(args...);
				}
				++us;
			}
			void pop_back() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (us) {
					if constexpr (std::is_trivially_destructible_v<T>) {
						--us;
					}
					else {
						a[--us].~T();
					}
				}
			}
			void pop_back(size_t count) noexcept(
				std::is_nothrow_destructible_v<T>
			) {
				if (count > us) {
					if constexpr (std::is_trivially_destructible_v<T>) {
						us = 0;
					}
					else {
						while (us) {
							a[--us].~T();
						}
					}
				}
				else {
					if constexpr (std::is_trivially_destructible_v<T>) {
						us -= count;
					}
					else {
						while (count) {
							a[--us].~T();
							--count;
						}
					}
				}
			}
			template<typename ...Args>
			void emplace(size_t index, Args&&... args) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_constructible_v<T, Args&&...>&&
				std::is_nothrow_destructible_v<T>
			){
				if (index < us) {
					provide_element_space();
					move_subarray_right(begin() + index, 1);
					if constexpr (std::is_trivially_constructible_v<T, Args&&...>) {
						*(begin() + index) = { args... };
					}
					else {
						new (begin() + index) T(args...);
					}
					++us;
				}
				else {
					emplace_back(args...);
				}
			}
			void insert(size_t index, const T& element) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>&&
				std::is_trivially_copy_constructible_v<T> ? std::is_nothrow_assignable_v<T&, const T&> : std::is_nothrow_copy_constructible_v<T>
			){
				if (index < us) {
					T* old_begin = a;
					const T* p = &element;
					provide_element_space();
					validate_pointer(old_begin, p, p > old_begin + index - 1 ? 1 : 0);
					move_subarray_right(begin() + index, 1);
					if constexpr (std::is_trivially_copy_constructible_v<T>) {
						*(begin() + index) = *p;
					}
					else {
						new (begin() + index) T(*p);
					}
					++us;
				}
				else {
					push_back(element);
				}
			}
			void insert(size_t index, const T& element, size_t count) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>&&
				std::is_trivially_copy_constructible_v<T> ? std::is_nothrow_assignable_v<T&, const T&> : std::is_nothrow_copy_constructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				if (count) {
					T* old_begin = a;
					const T* p = &element;
					provide_subarray_space(count);
					validate_pointer(old_begin, p, p > old_begin + index - 1 ? count : 0);
					if (index < us) {
						old_begin = begin() + index;
						move_subarray_right(old_begin, count);
						us += count;
						old_begin += count;
						while (count) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*--old_begin = *p;
							}
							else {
								new (--old_begin) T(*p);
							}
							--count;
						}
					}
					else {
						old_begin = end();
						while (count) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*old_begin = *p;
							}
							else {
								new (old_begin) T(*p);
							}
							++old_begin;
							--count;
						}
					}
					us += count;
				}
			}
			void insert(size_t index, T&& element) noexcept(
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_constructible_v<T, T&&>&&
				std::is_nothrow_destructible_v<T>
			){
				emplace(index, std::move(element));
			}
			void insert(size_t index, const T* first, const T* last) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>&&
				std::is_trivially_copy_constructible_v<T> ? std::is_nothrow_assignable_v<T&, const T&> : std::is_nothrow_copy_constructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				size_t count = last - first;
				T* old_begin = a;
				provide_subarray_space(count);
				validate_pointer(old_begin, first, first < old_begin + index ? 0 : count);
				validate_pointer(old_begin, last,  last < old_begin + index ? 0 : count);
				if (index < us) {
					old_begin = begin() + index;
					move_subarray_right(old_begin, count);
					old_begin += count;
					if (last - first != count) {
						//we need to iter: first -> beging() + index & beging() + index + count -> last
						T* s = old_begin;
						while (s != last) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*old_begin = *--last;
							}
							else {
								new (old_begin) T(*--last);
							}
						}
						s = begin() + index;
						while (s != first) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*old_begin = *--s;
							}
							else {
								new (old_begin) T(*--s);
							}
						}
					}
					else {
						while (first != last) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*--old_begin = *--last;
							}
							else {
								new (--old_begin) T(*--last);
							}
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
			//erase from array - slow and save order
			void erase(T* pos) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				if (pos < back()) {
					if constexpr (!std::is_trivially_destructible_v<T>) {
						pos->~T();
					}
					move_subarray_left(++pos, 1);
					--us;
				}
				else {
					pop_back();
				}
			}
			void erase(T* first, T* last) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				us -= last - first;
				if constexpr (std::is_trivially_destructible_v<T>) {
					if (last != end()) {
						move_subarray_left(last, last - first);
					}
				}
				else {
					if (last == end()) {
						while (last != first) {
							(--last)->~T();
						}
					}
					else {
						move_subarray_left(last, last - first);
					}
				}
			}
			//remove from array - fast and may unsort
			void remove(T* pos) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				if constexpr (!std::is_trivially_destructible_v<T>) {
					pos->~T();
				}
				if (pos - a != --us) {
					*pos = std::move(a[us]);
				}
			}
			void remove(T* first, T* last) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>
			){
				#ifdef DA_DEBUG
					//to do
				#endif
				while (first != last) {
					remove(--last);
				}
			}
			void clear() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if constexpr (!std::is_trivially_destructible_v<T>) {
					T* i = end();
					while (i != a) {
						(--i)->~T();
					}
				}
				free(a);
				a = nullptr;
				us = 0;
				as = 0;
			}
			//get methods
			size_t get_used_size() const noexcept {
				return us;
			}
			size_t get_allocated_size() const noexcept {
				return as;
			}
	};
	//string definition and string relared helpers
	typedef dynamic_array<char> dynamic_string;
	typedef dynamic_array<wchar_t> dynamic_wstring;
	#define SECURE_STR_MERGE(str)		\
		if ((str).get_used_size()) {	\
			if (!*(str).back()) {		\
				(str).pop_back();		\
			}							\
		}
}