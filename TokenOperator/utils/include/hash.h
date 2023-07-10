#pragma once
#include "type_info.h"
namespace utils {
	//template for iterable hashes, where iteration is independannt result
	template<typename IN, typename OUT> constexpr inline
	OUT	iterable_hash(const IN* in, size_t in_size, auto iterable_hash_lamda) {
		static_assert(
			!(sizeof(OUT) < sizeof(IN)), 
			"iterable_hash can`t generate output type smaller than input type"
		);
		static_assert(
			!type_in_type_wholes<IN, OUT>(),
			"iterable_hash can`t input type must fil entirely output type"
		);
		//to do "static warning", when sizeof(in)*in_size=OUT
		OUT result;
		IN* out_pointer = (IN*)&result;
		//make result = 0, supports arrays with constant legth (like int[2])
		size_t i = type_in_type_capasity<IN, OUT>(), ii = 0;
		while (i) {
			out_pointer[--i] = 0;
		}
		//calculate hash, IN size is already a STEP size
		i = type_in_type_capasity<IN, OUT>();
		while (in_size) {
			out_pointer[ii] = iterable_hash_lamda(out_pointer[ii], in[--in_size]);
			if (++ii == i) {
				ii = 0;
			}
		}
		return result;
	}
	template<typename IN, typename OUT> constexpr inline
	OUT	pearson_hash(const IN* in, size_t in_size = 1) {
		return iterable_hash<IN, OUT>(
			in, in_size,
			[](IN& out_step, const IN& in_step) {
				return out_step ^ in_step;
			}
		);
	};
}