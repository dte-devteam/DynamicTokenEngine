module;
#include <initializer_list>
#include <new>	//to do - find out why fixes error C2661 with operator new
export module utils.dynamic_memory.dynamic_stack;
import constraints; 
import memory;
export namespace dte_utils {
	template<typename T>
	concept dyn_memory_limit = !(
		std::is_void_v<T> ||			//can`t return void
		std::is_unbounded_array_v<T>	//cant manage T[]
		) &&
		std::is_destructible_v<T>			//will destruct all data in destructor
	;

	/*
	Operates with non-new array
	*/
	template<dyn_memory_limit T>
	struct dynamic_stack {
		protected:
			size_t	us;	//used size
			size_t	as;	//allocated size
			T* a;		//array
			//us value MUST be in range of array! 
			void destruct_array() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(begin(), end());
				}
				free(a);
			}
			void provide_element_space() {
				if (as == us) {
					resize_allocated(as * 2 + 1);
				}
			}
			void provide_array_space(size_t required_size) {
				if (get_alloc_size() < required_size) {
					resize_allocated(required_size);
				}
			}

			template<copy_constructible<T> U>
			void _push_back(const U& value) {
				if constexpr (std::is_trivially_constructible_v<T, const U&>) {
					a[us] = static_cast<T>(value);
				}
				else {
					new (end()) T(static_cast<T>(value));
				}
				++us;
			}
			template<move_constructible<T> U>
			void _push_back(U&& value) {
				if constexpr (std::is_trivially_constructible_v<T, U&&>) {
					a[us] = static_cast<T&&>(value);
				}
				else {
					new (end()) T(static_cast<T&&>(value));
				}
				++us;
			}
			template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
			void _emplace_back(Args&&... args) {
				new (end()) T(std::forward<Args>(args)...);
				++us;
			}
		public:
			dynamic_stack() : us(0), as(0), a(nullptr) {}
			dynamic_stack(size_t alocate_size) : us(0), as(alocate_size), a(as ? malloc_t<T>(as) : nullptr) {}
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack(const U(&array)[N], size_t reserved_size = 0) : dynamic_stack(array, N, reserved_size) {}
			template<copyable_or_movable<T> U>
			dynamic_stack(const U* array, size_t used_size, size_t reserved_size) : us(used_size), as(us + reserved_size), a(malloc_t<T>(as)) {
				array_to_array(begin(), array, get_used_size());
			}

			template<copyable_or_movable<T> U>
			dynamic_stack(std::initializer_list<U> il, size_t reserved_size = 0) : dynamic_stack(il.begin(), il.size(), reserved_size) {}

			dynamic_stack(const dynamic_stack& dyn_array) : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(as ? malloc_t<T>(as) : nullptr) {
				array_to_array(begin(), dyn_array.begin(), get_used_size());
			}
			dynamic_stack(dynamic_stack&& dyn_array) noexcept : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(dyn_array.begin()) {
				dyn_array.us = 0;
				dyn_array.a = nullptr;
			}

			template<copyable_or_movable<T> U>
			dynamic_stack(const dynamic_stack<U>& dyn_array) : us(dyn_array.get_used_size()), as(dyn_array.get_alloc_size()), a(as ? malloc_t<T>(as) : nullptr) {
				array_to_array(begin(), dyn_array.begin(), get_used_size());
			}

			~dynamic_stack() {
				destruct_array();
			}

			//for(T& t : dyn_array)
			T* begin() {
				return a;
			}
			const T* begin() const {
				return a;
			}
			T* end() {
				return a + us;
			}
			const T* end() const {
				return a + us;
			}

			T& front() {
				//TODO: if fize < 1 (error - out of range)
				return *begin();
			}
			const T& front() const {
				//TODO: if fize < 1 (error - out of range)
				return *begin();
			}
			T& back() {
				//TODO: if fize < 1 (error - out of range)
				return *(end() - 1);
			}
			const T& back() const {
				//TODO: if fize < 1 (error - out of range)
				return *(end() - 1);
			}
			//
			template<typename P>
			T* find(P predicate) {
				T* i = end();
				while (i != a) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			template<typename P>
			const T* find(P predicate) const {
				T* i = end();
				while (i != a) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			template<typename P>
			T* find_ranged(P predicate, size_t from, size_t to) {
				//TODO: if from > to (error - invalid range)
				//TODO: if to > us (error - out of range)
				T* i = a + to;
				T* s = a + from;
				while (i != s) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}
			template<typename P>
			const T* find_ranged(P predicate, size_t from, size_t to) const {
				//TODO: if from > to (error - invalid range)
				//TODO: if to > us (error - out of range)
				T* i = a + to;
				T* s = a + from;
				while (i != s) {
					if (predicate(*--i)) {
						return i;
					}
				}
				return nullptr;
			}

			size_t get_alloc_size() const {
				return as;
			}
			size_t get_used_size() const {
				return us;
			}
			bool empty() const {
				return !get_used_size();
			}

			//doesn`t applyable for insert operation
			void resize_allocated(size_t size) {
				if (!size) {
					destruct_array();
					us = as = 0;
					a = nullptr;
					return;
				}
				if (get_used_size() > size) {
					if constexpr (!std::is_trivially_destructible_v<T>) {
						destruct_range(begin() + size, end());
					}
					us = size;
				}
				if (as != size) {
					if constexpr (std::is_trivially_move_constructible_v<T>) {
						a = realloc_t(begin(), size);
					}
					else {
						T* buffer = malloc_t<T>(size);
						array_to_array(buffer, begin(), get_used_size());
						if constexpr (!std::is_trivially_destructible_v<T>) {
							destruct_range(begin(), end());
						}
						free(begin());
						a = buffer;
					}
					as = size;
				}
			}
			void clear() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(begin(), end());
				}
				us = 0;
			}
			//----------------
			template<copy_constructible<T> U>
			void push_back(const U& value) {
				provide_element_space();
				_push_back(value);
			}
			template<move_constructible<T> U>
			void push_back(U&& value) {
				provide_element_space();
				_push_back(value);
			}
			template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
			void emplace_back(Args&&... args) {
				provide_element_space();
				_emplace_back(args...);
			}
			void pop_back() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					a[--us].~T();
				}
				else {
					--us;
				}
			}
			void pop_back(size_t num) {
				//TODO: num > us (error out of range)
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(end() - num, end());
				}
				else {
					us -= num;
				}
			}
			//----------------
			T& operator[](size_t index) {
				return a[index];
			}
			const T& operator[](size_t index) const {
				return a[index];
			}
			//assing operators
			dynamic_stack& operator =(const dynamic_stack& dyn_array) {
				if (this == &dyn_array) {
					return *this;
				}
				destruct_array();
				us = dyn_array.get_used_size();
				as = dyn_array.get_alloc_size();
				a = malloc_t<T>(get_alloc_size());
				array_to_array(begin(), dyn_array.begin(), get_used_size());
				return *this;
			}
			dynamic_stack& operator =(dynamic_stack&& dyn_array) noexcept {
				if (this == &dyn_array) {
					return *this;
				}
				std::swap(a, dyn_array.a);
				std::swap(as, dyn_array.as);
				std::swap(us, dyn_array.us);
				return *this;
			}

			dynamic_stack& operator +=(const dynamic_stack& dyn_array) {
				provide_array_space(get_used_size() + dyn_array.get_used_size());
				array_to_array(end(), dyn_array.get_alloc_size(), dyn_array.get_used_size());
				us += dyn_array.get_used_size();
				return *this;
			}
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack& operator +=(const U(&array)[N]) {
				provide_array_space(get_used_size() + N);
				array_to_array(end(), array, N);
				us += N;
				return *this;
			}

			dynamic_stack operator+(const dynamic_stack& dyn_array) const {
				dynamic_stack<T> new_array(begin(), get_used_size(), dyn_array.get_used_size());
				new_array += dyn_array;
				return new_array;
			}
			dynamic_stack operator+(dynamic_stack&& dyn_array) const {
				if (dyn_array.get_alloc_size() < dyn_array.get_used_size() + get_used_size()) {
					T* buffer = malloc_t<T>(dyn_array.get_used_size() + get_used_size());
					array_to_array(buffer, begin(), get_used_size());
					array_to_array(buffer + get_used_size(), dyn_array.begin(), dyn_array.get_used_size());
					dyn_array.destruct_array();
					dyn_array.a = buffer;
					dyn_array.us += get_used_size();
					return dyn_array;
				}
				else {
					array_to_array(dyn_array.begin() + get_used_size(), dyn_array.begin(), dyn_array.get_used_size());
					array_to_array(dyn_array.begin(), begin(), get_used_size());
					dyn_array.us += us;
					return dyn_array;
				}
			}

			//should be faster than +dynamic_stack&& because of no reallocation
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack operator+(const U(&array)[N]) {
				dynamic_stack new_array(begin(), get_used_size(), N);
				array_to_array(new_array.end(), array, N);
				new_array.us += N;
				return new_array;
			}
	};
}
