#pragma once
//currenty unactive error VVV
//#include <new>	//to do - find out why fixes error C2661 with operator new
#include "../../target_architecture.h"
#include "constraints.h"
namespace dte_utils {
	template<typename T>
	inline T* malloc_t(size_t size) {
		return reinterpret_cast<T*>(malloc(sizeof(T) * size));
	}
	template<typename T>
	inline T* realloc_t(T* block, size_t size) {
		return reinterpret_cast<T*>(realloc(block, sizeof(T) * size));
	}

	template<typename T, typename ...Args> requires std::is_constructible_v<T, Args&&...>
	inline T* construct_range(T* begin, T* end, Args&&... args) {
		while (begin != end) {
			new (--end) T(std::forward<Args>(args)...);
		}
		return begin;
	}

	template<typename U, copy_constructible<U> T>
	inline void copy_range(const T* begin, const T* end, U* dest_end) {
		while (begin != end) {
			new (--dest_end) U(static_cast<U>(*--end));
		}
	}
	template<typename U, move_constructible<U> T>
	inline void move_range(T* begin, T* end, U* dest_end) {
		while (begin != end) { 
			new (--dest_end) U(static_cast<U&&>(*--end));
		}
	}
	template<typename T> requires std::is_destructible_v<T>
	inline void destruct_range(T* begin, T* end) {
		while (begin != end) {
			(--end)->~T();
		}
	}

	//Copies memory by char/CPU_WORD (count = number of bytes)
	inline void* copy_memory(void* dest, const void* src, size_t count) {
		if (!(
			(uintptr_t)dest % sizeof(CPU_WORD) ||
			(uintptr_t)src % sizeof(CPU_WORD) ||
			count % sizeof(CPU_WORD)
		)) {
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

	template<typename U, copy_constructible<U> T>
	inline void array_to_array(U* dest, const T* src, size_t count) {
		if constexpr (std::is_trivial_v<U> && std::is_same_v<T, U>) {
			copy_memory(dest, src, count * sizeof(U));
		}
		else {
			copy_range(src, src + count, dest + count);
		}
	}

	template<typename U, copyable_or_movable<U> T>
	inline void array_to_array(U* dest, T* src, size_t count) {
		if constexpr (std::is_trivial_v<U> && std::is_same_v<T, U>) {
			copy_memory(dest, src, count * sizeof(U));
		}
		else if constexpr (move_constructible<T, U>) {
			move_range(src, src + count, dest + count);
		}
		else {
			copy_range(src, src + count, dest + count);
		}
	}
}