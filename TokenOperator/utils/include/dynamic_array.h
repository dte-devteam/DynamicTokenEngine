#pragma once
#include <new>	//to do - find out why fixes error C2661 with operator new
#include <type_traits>

#include <iostream>
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
			void validate_pointer(const T* old_begin, const T*& pointer, size_t movement) const {
				if (!pointer_out_of_array(pointer)) {
					pointer += a - old_begin + movement;
				}
			}
			//raw methods without any checks
			template<typename U>
			void _push_back(U&& element) noexcept(
				std::is_nothrow_constructible_v<T, U>
			){
				if constexpr (std::is_trivially_constructible_v<T, U>) {
					a[us] = element;
				}
				else {
					new (end()) T(element);
				}
				++us;
			}
			void _pop_back() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				--us;
				if constexpr (!std::is_trivially_destructible_v<T>) {			
					a[us].~T();
				}
			}
			template<typename U>
			void _insert(size_t index, U&& element) noexcept(
				std::is_nothrow_constructible_v<T, U>
			){
				if constexpr (std::is_trivially_constructible_v<T, U>) {
					a[index] = element;
				}
				else {
					new (a + index) T(element);
				}
			}
			template<typename ...Args>
			void _emplace(size_t index, Args&&... args) noexcept(
				std::is_nothrow_constructible_v<T, Args>
			){
				if constexpr (std::is_trivially_constructible_v<T, Args&&...>) {
					a[index] = { args... };
				}
				else {
					new (a + index) T(args...);
				}
			}
		public:
			dynamic_array() : dynamic_array(nullptr, 0) {}
			template<size_t N>
			dynamic_array(const T (&array)[N]) : dynamic_array(array, N, 0) {}
			template<size_t N>
			dynamic_array(T (&&array)[N]) : as(N), us(N), a((T*)malloc(sizeof(T)* as)) {
				T* target = a;
				for (const T& element : array) {
					if constexpr (std::is_trivially_move_constructible_v<T>) {
						*target = std::move(element);
					}
					else {
						new (target) T(std::move(element));
					}
					++target;
				}
			}
			/*
			DO NOT use allocated array by "new"!
			This struct uses ONLY "free". Don`t mix them!
			This constructor STORES array WITHOUT COPYING!
			*/
			dynamic_array(T* array, size_t use_size) : as(use_size), us(use_size), a(array)  {}
			dynamic_array(const T* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a((T*)malloc(sizeof(T) * as)) {
				const T* source = array + us;
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
			dynamic_array(dynamic_array<T>&& dyn_array) noexcept : as(std::exchange(dyn_array.as, 0)), us(std::exchange(dyn_array.us, 0)), a(std::exchange(dyn_array.a, nullptr)) {}
			template<size_t N, typename U>
			dynamic_array(const U (&array)[N]) : dynamic_array(array, N, 0) {}
			template<size_t N, typename U>
			dynamic_array(U (&&array)[N]) : as(N), us(N), a((T*)malloc(sizeof(T)* as)) {
				T* target = a;
				for (const U& element : array) {
					if constexpr (std::is_trivially_constructible_v<T, U&&>) {
						*target = std::move(element);
					}
					else {
						new (target) T(std::move(element));
					}
					++target;
				}
			}
			template<typename U>
			dynamic_array(const U* array, size_t use_size, size_t reserve_size) : as(use_size + reserve_size), us(use_size), a((T*)malloc(sizeof(T) * as)) {
				const U* source = array + us;
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
			dynamic_array(dynamic_array<U>&& dyn_array) noexcept : as(std::move(dyn_array.as)), us(std::move(dyn_array.us)), a((T*)(malloc(sizeof(T) * as))) {
				for (const U& element : dyn_array) {
					_push_back(std::move(element));
				}
			}
			~dynamic_array() {
				//if you got _debugbreak() here - you used wrong constructor:
				//for T/U array[N] there is dynamic_array(T/U (&array)[N]) - it will copy it
				//dynamic_array(T/U* array, size_t use_size) is allowed only for new T/U[N] - it will hold array by pointer
				//dynamic_array(T/U* array, size_t use_size) ensures that we won`t make useless duplicate
				if constexpr (!std::is_trivially_destructible_v<T>) {
					while (us) {
						_pop_back();
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
			template<typename U>
			dynamic_array<T>& operator =(const dynamic_array<U>& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				if (as < dyn_array.us) {
					if constexpr (std::is_trivially_destructible_v<T>) {
						us = 0;
					}
					else {
						while (us) {
							_pop_back();
						}
					}
					free(a);
					as = dyn_array.us;
					a = (T*)malloc(sizeof(T) * as);
				}
				for (const U& element : dyn_array) {
					_push_back(element);
				}
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator =(dynamic_array<U>&& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				if constexpr (std::is_same_v<T, U>) {
					swap(dyn_array);
				}
				else {
					if constexpr (std::is_trivially_destructible_v<T>) {
						us = 0;
					}
					else {
						while (us) {
							_pop_back();
						}
					}
					free(a);
					as = dyn_array.us;
					a = (T*)malloc(sizeof(T) * as);
					for (const U& element : dyn_array) {
						_push_back(std::move(element));
					}
				}
				return *this;
			}
			template<size_t N, typename U>
			dynamic_array<T>& operator =(const U (&array)[N]) {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					us = 0;
				}
				else {
					while (us) {
						_pop_back();
					}
				}
				free(a);
				as = N;
				a = (T*)malloc(sizeof(T) * as);
				for (const U& element : array) {
					_push_back(element);
				}
				return *this;
			}
			template<size_t N,typename U>
			dynamic_array<T>& operator =(U (&&array)[N]) {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					us = 0;
				}
				else {
					while (us) {
						_pop_back();
					}
				}
				free(a);
				as = N;
				a = (T*)malloc(sizeof(T) * as);
				for (const U& element : array) {
					_push_back(std::move(element));
				}
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator +=(const dynamic_array<U>& dyn_array) noexcept (
				noexcept(_push_back(std::declval<const U&>()))
			){
				provide_subarray_space(dyn_array.us);
				for (const U& element : dyn_array) {
					_push_back(element);
				}
				return *this;
			}
			template<typename U>
			dynamic_array<T>& operator +=(dynamic_array<U>&& dyn_array) noexcept (
				noexcept(_push_back(std::declval<U>()))
			){
				provide_subarray_space(dyn_array.us);
				for (const U& element : dyn_array) {
					_push_back(std::move(element));
				}
				return *this;
			}
			template<size_t N, typename U>
			dynamic_array<T>& operator +=(const U(&array)[N]) {
				provide_subarray_space(N);
				for (const U& element : array) {
					_push_back(element);
				}
				return *this;
			}
			template<size_t N, typename U>
			dynamic_array<T>& operator +=(U (&&array)[N]) {
				provide_subarray_space(N);
				for (const U& element : array) {
					_push_back(std::move(element));
				}
				return *this;
			}
			template<typename U>
			dynamic_array<T> operator +(const dynamic_array<U>& dyn_array) const {
				dynamic_array<T> result(a, us, dyn_array.us);
				for (const U& element : dyn_array) {
					result._push_back(element);
				}
				return result;
			}
			template<typename U>
			dynamic_array<T> operator +(dynamic_array<U>&& dyn_array) const {
				dynamic_array<T> result(a, us, dyn_array.us);
				for (const U& element : dyn_array) {
					result._push_back(syd::move(element));
				}
				return result;
			}
			template<size_t N, typename U>
			dynamic_array<T> operator +(const U (&array)[N]) const {
				dynamic_array<T> result(a, us, N);
				for (const U& element : array) {
					result._push_back(element);
				}
				return result;
			}
			template<size_t N, typename U>
			dynamic_array<T> operator +(U (&&array)[N]) const {
				dynamic_array<T> result(a, us, N);
				for (const U& element : array) {
					result._push_back(std::move(element));
				}
				return result;
			}
			template<size_t N, typename T, typename U>
			friend dynamic_array<T> operator +(U(&& array)[N], dynamic_array<T>&& dyn_array);
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
					for (const T& i : dyn_array) {
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
			void resize_allocated(size_t size) noexcept(
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
					a = (T*)realloc(a, sizeof(T) * size);
					return;
				}
				T* new_array = (T*)realloc(a, sizeof(T) * size);
				if (new_array) {
					as = size;
					a = new_array;
				}
			}
			void provide_element_space() noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (us == as) {
					resize_allocated(as + 1);
				}
			}
			void provide_subarray_space(size_t size) noexcept(
				std::is_nothrow_destructible_v<T>
			){
				if (us + size > as) {
					resize_allocated(us + size);
				}
			}
			//--------------------------------------
			template<typename U>
			void push_back(U&& element) noexcept(
				noexcept(provide_element_space()) &&
				noexcept(_push_back(element))
			){
				//does need pointer validation?
				provide_element_space();
				_push_back(element);
			}
			template<typename ...Args>
			void emplace_back(Args&&... args) noexcept(
				noexcept(provide_element_space()) &&
				noexcept(_emplace(us, args...))
			){
				provide_element_space();
				_emplace(us, args...);
				++us;
			}
			void pop_back() noexcept(
				noexcept(_pop_back())
			){
				if (us) {
					_pop_back();
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
							_pop_back();
						}
					}
				}
				else {
					if constexpr (std::is_trivially_destructible_v<T>) {
						us -= count;
					}
					else {
						while (count) {
							_pop_back();
							--count;
						}
					}
				}
			}
			template<typename ...Args>
			void emplace(size_t index, Args&&... args) noexcept(
				noexcept(provide_element_space()) &&
				noexcept(move_subarray_right(begin() + index, 1)) &&
				noexcept(_emplace(us, args...))
			){
				if (index < us) {
					provide_element_space();
					move_subarray_right(begin() + index, 1);
					_emplace(us, args...);
					++us;
				}
				else {
					emplace_back(args...);
				}
			}
			template<typename U>
			void insert(size_t index, U&& element) noexcept(
				noexcept(provide_element_space()) &&
				noexcept(move_subarray_right(nullptr, 0)) &&
				noexcept(_insert(index, element)) &&
				noexcept(push_back(element))
			){
				if (index < us) {
					const T* old_begin = a;
					const T* p = (T*)&element;
					provide_element_space();
					validate_pointer(old_begin, p, p > old_begin + index - 1 ? 1 : 0);
					move_subarray_right(begin() + index, 1);
					if constexpr (!std::is_lvalue_reference_v<U>) {
						_insert(index, std::move(*(std::decay_t<U>*)p));
					}
					else {
						_insert(index, *(std::decay_t<U>*)p);
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
						us += count;
					}
				}
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
						while (old_begin != last) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*--old_begin = *--last;
							}
							else {
								new (--old_begin) T(*--last);
							}
						}
						T* s = begin() + index;
						while (s != first) {
							if constexpr (std::is_trivially_copy_constructible_v<T>) {
								*--old_begin = *--s;
							}
							else {
								new (--old_begin) T(*--s);
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
			template<size_t N>
			void insert(size_t index, const T (&array)[N]) noexcept (
				std::is_nothrow_move_constructible_v<T>&&
				std::is_nothrow_move_assignable_v<T>&&
				std::is_nothrow_destructible_v<T>&&
				std::is_trivially_copy_constructible_v<T> ? std::is_nothrow_assignable_v<T&, const T&> : std::is_nothrow_copy_constructible_v<T>
			){
				insert(index, array, array + N);
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
	template<size_t N, typename T, typename U>
	dynamic_array<T> operator +(const U (&array)[N], const dynamic_array<T>& dyn_array) {
		dynamic_array<T> result(array, N, dyn_array.get_used_size());
		for (const T& element : dyn_array) {
			result.push_back(element);
		}
		return result;
	}
	template<size_t N, typename T, typename U>
	dynamic_array<T> operator +(U (&&array)[N], const dynamic_array<T>& dyn_array) {
		dynamic_array<T> result(nullptr, 0, N + dyn_array.get_used_size());
		for (const U& element : array) {
			result.push_back(std::move(element));
		}
		for (const T& element : dyn_array) {
			result.push_back(element);
		}
		return result;
	}
	template<size_t N, typename T, typename U>
	dynamic_array<T> operator +(const U (&array)[N], dynamic_array<T>&& dyn_array) {
		dyn_array.insert(0, array);
		return dyn_array;
	}
	template<size_t N, typename T, typename U>
	dynamic_array<T> operator +(U(&& array)[N], dynamic_array<T>&& dyn_array) {
		dyn_array.provide_subarray_space(N);
		T* i = dyn_array.begin();
		dyn_array.move_subarray_right(i, N);
		for (const U& element : array) {
			if constexpr (std::is_trivially_constructible_v<T, U&&>) {
				*i = std::move(element);
			}
			else {
				new (i) T(std::move(element));
			}
			++i;
		}
		dyn_array.us += N;
		return dyn_array;
	}
}