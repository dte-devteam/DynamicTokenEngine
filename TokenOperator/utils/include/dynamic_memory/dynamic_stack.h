#pragma once
#include "memory.h"
#include <initializer_list>
#include <new>	//to do - find out why fixes error C2661 with operator new
namespace dte_utils {
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
			T*		a;	//array
			//us value MUST be in range of array! 
			void destruct_array();
			void provide_element_space();
			void provide_array_space(size_t required_size);

			template<copy_constructible<T> U>
			void _push_back(const U& value);
			template<move_constructible<T> U>
			void _push_back(U&& value);
			template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
			void _emplace_back(Args&&... args);
		public:
			dynamic_stack();
			dynamic_stack(size_t alocate_size);
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack(const U(&array)[N], size_t reserved_size = 0);
			template<copyable_or_movable<T> U>
			dynamic_stack(const U* array, size_t used_size, size_t reserved_size);

			template<copyable_or_movable<T> U>
			dynamic_stack(std::initializer_list<U> il, size_t reserved_size = 0);

			dynamic_stack(const dynamic_stack& dyn_array);
			dynamic_stack(dynamic_stack&& dyn_array) noexcept;

			template<copyable_or_movable<T> U>
			dynamic_stack(const dynamic_stack<U>& dyn_array);

			~dynamic_stack(); 

			//for(T& t : dyn_array)
			T* begin();
			const T* begin() const;
			T* end();
			const T* end() const;

			T& front();
			const T& front() const;
			T& back();
			const T& back() const;
			//
			template<typename P>
			T* find(P predicate);
			template<typename P>
			const T* find(P predicate) const;
			template<typename P>
			T* find_ranged(P predicate, size_t from, size_t to);
			template<typename P>
			const T* find_ranged(P predicate, size_t from, size_t to) const;
			
			size_t get_alloc_size() const;
			size_t get_used_size() const;
			bool empty() const;
			
			//doesn`t applyable for insert operation
			void resize_allocated(size_t size);
			void clear();
			//----------------
			template<copy_constructible<T> U>
			void push_back(const U& value);
			template<move_constructible<T> U>
			void push_back(U&& value);
			template<typename ...Args> requires std::is_constructible_v<T, Args&&...>
			void emplace_back(Args&&... args);
			void pop_back();
			//----------------
			T& operator[](size_t index) {
				return a[index];
			}
			const T& operator[](size_t index) const {
				return a[index];
			}
			//assing operators
			dynamic_stack& operator =(const dynamic_stack& dyn_array);
			dynamic_stack& operator =(dynamic_stack&& dyn_array) noexcept;
			
			dynamic_stack& operator +=(const dynamic_stack& dyn_array);
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack& operator +=(const U(&array)[N]);

			dynamic_stack operator+(const dynamic_stack& dyn_array) const;
			dynamic_stack operator+(dynamic_stack&& dyn_array) const;

			//should be faster than +dynamic_stack&& because of no reallocation
			template<copyable_or_movable<T> U, size_t N>
			dynamic_stack operator+(const U(&array)[N]);
	};
}