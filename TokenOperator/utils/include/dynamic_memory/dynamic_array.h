#pragma once
#include "dynamic_stack.h"
namespace dte_utils {
	template<dyn_memory_limit T>
	struct dynamic_array : dynamic_stack<T> {
		template<dyn_memory_limit U> friend struct dynamic_array;
		using dynamic_stack<T>::dynamic_stack;
		


		void insert() {}




		void erase() {}
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
					this->a[this->us].~T();
				}
			}
		}
		
	};
}