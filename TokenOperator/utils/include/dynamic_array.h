#pragma once
#include <type_traits>
#include <cstring>
#include "memory.h"
#include "constraints.h"
namespace dte_utils {
	/*
	Operates with non-new array
	*/
	template<typename T>
	struct dynamic_array {
		protected:
			size_t	us;	//used size
			size_t	as;	//allocated size
			T*		a;	//array
		public:
			dynamic_array() : us(0), as(0), a(nullptr) {}
			dynamic_array(size_t alocate_size) : us(0), as(alocate_size), a(as ? malloc_t<T>(as) : nullptr) {}
			template<Castable<T> U, size_t N>
			dynamic_array(const U (&array)[N], size_t reserved_size = 0) : dynamic_array(array, N, reserved_size) {}
			template<Castable<T> U>
			dynamic_array(const U* array, size_t used_size, size_t reserved_size = 0) : us(used_size), as(us + reserved_size), a(malloc_t<T>(as)) {
				if constexpr (std::is_trivially_copyable_v<T> && std::is_same_v<T, U>) {
					copy_memory(a, array, us * sizeof(T));
				}
				else {
					copy_range(array, array + us, a);
				}
			}



			dynamic_array(const dynamic_array& array) : us(array.us), as(array.as), a(as ? malloc_t<T>(as) : nullptr) {
				if constexpr (std::is_trivially_copyable_v<T>) {
					copy_memory(a, array, used_size * sizeof(T));
				}
				else {
					copy_range(array, array + used_size, a);
				}
			}

			
			

			dynamic_array(dynamic_array&& array) : us(array.us), as(array.as), a(array.a) noexcept {
				array.us = 0;
				array.a = nullptr;
			}
			



			~dynamic_array() {
				if constexpr (!std::is_trivially_destructible_v<T>) {
					destruct_range(a, a + us);
				}
				//free(a);
			}
			


			//
			T* begin() const {
				return a;
			}
			T* end() const {
				return a + us;
			}
	};
}