#pragma once
#include "dynamic_stack.h"
namespace dte_utils {
	template<dyn_memory_limit T>
	struct dynamic_array : dynamic_stack<T> {
		using dynamic_stack<T>::dynamic_stack;
		protected:
			T* new_spased_buffer(size_t new_size, T* gap_pos, size_t gap_size);
		public:
			template<copy_constructible<T> U>
			void insert(T* pos, const U& value);
			template<move_constructible<T> U>
			void insert(T* pos, U&& value);
			template<copy_constructible<T> U>
			void insert(T* pos, const U& value, size_t num);
			template<copy_constructible<T> U>
			void insert(T* pos, const U* first, const U* last);
			template<copy_constructible<T> U>
			void insert(T* pos, std::initializer_list<U> il);

			template<typename ...Args>
			void emplace(T* pos, Args&&... args) requires std::is_constructible_v<T, Args&&...>;

			void erase(T* pos);
			void erase(T* first, T* last);
		
			//unordered removal (faster, but order breaks)
			void remove(T* pos);
			//is effective in larger arrays and smaller removal
			void remove(T* first, T* last);
	};
}