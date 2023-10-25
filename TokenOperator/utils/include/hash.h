#pragma once
#include "type_info.h"
namespace utils {
	//template for iterable hashes, where iteration is independannt result
	template<typename T, typename U> constexpr inline
	U iterable_hash(const T* in, size_t in_size, auto iterable_hash_lamda) {
		static_assert(
			!(sizeof(U) < sizeof(T)), 
			"iterable_hash can`t generate output type smaller than input type"
		);
		static_assert(
			!type_in_type_wholes<T, U>(),
			"iterable_hash can`t input type must fil entirely output type"
		);
		//to do "static warning", when sizeof(in)*in_size=OUT
		U result;
		T* out_pointer = (T*)&result;
		//make result = 0, supports arrays with constant legth (like int[2])
		size_t i = type_in_type_capasity<T, U>(), ii = 0;
		while (i) {
			out_pointer[--i] = 0;
		}
		//calculate hash, IN size is already a STEP size
		i = type_in_type_capasity<T, U>();
		while (in_size) {
			out_pointer[ii] = iterable_hash_lamda(out_pointer[ii], in[--in_size]);
			if (++ii == i) {
				ii = 0;
			}
		}
		return result;
	}
	template<typename T, typename U> constexpr inline
	U pearson_hash(const T* in, size_t in_size = 1) {
		return iterable_hash<T, U>(
			in, in_size,
			[](T& out_step, const T& in_step) {
				return out_step ^ in_step;
			}
		);
	};
}