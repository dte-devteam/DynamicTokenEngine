#pragma once
#include <new>	//to do - find out why fixes error C2661 with operator new
#include "../../target_architecture.h"
namespace dte_utils {
	template<typename T>
	T* malloc_t(size_t size) {
		return reinterpret_cast<T*>(malloc(sizeof(T) * size));
	}
	template<typename T>
	inline void construct_range(T* begin, T* end) {
		while (begin != end) {
			new (begin) T;
			++begin;
		}
	}
	template<typename T, typename U>
	inline void copy_range(const T* begin, const T* end, U* dest) {
		while (begin != end) {
			new (dest) U(*begin);
			++begin;
			++dest;
		}
	}
	template<typename T>
	inline void destruct_range(T* begin, T* end) {
		while (begin != end) {
			begin->~T();
			++begin;
		}
	}
	//Copies memory by char/CPU_WORD (count = number of bytes)
	inline void* copy_memory(void* dest, const void* src, size_t count) {
		if ((uintptr_t)dest % sizeof(CPU_WORD) ==
			(uintptr_t)src % sizeof(CPU_WORD) ==
			count % sizeof(CPU_WORD) == 0) {
			count /= sizeof(CPU_WORD);
			while (count) {
				((CPU_WORD*)dest)[count] = ((const CPU_WORD*)src)[--count];
			}
		}
		else {
			while (count) {
				((char*)dest)[count] = ((const char*)src)[--count];
			}
		}
		return dest;
	}
}