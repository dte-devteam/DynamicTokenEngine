#pragma once
namespace dte_utils {
	template<typename T, typename U, typename I = char>
	inline constexpr U iterable_hash(const T* data, void (*hash_function)(I&, const I*), size_t num = 1) {
		static_assert(
			!(sizeof(T) % sizeof(I)),
			"iterable_hash can`t be generated if iteration will overcover data"
		);
		static_assert(
			!(sizeof(U) % sizeof(I)),
			"iterable_hash can`t be generated if iteration will overcover result"
		);
		U result = 0;
		I* r_pointer = (I*)&result;
		const I* d_pointer = (const I*)data;
		while (d_pointer != (const I*)(data + num)) {
			if (r_pointer == (I*)(&result + 1)) {
				r_pointer = (I*)&result;
			}
			hash_function(*r_pointer, d_pointer);
			++r_pointer;
			++d_pointer;
		}
		return result;
	}
	template<typename T, typename U, typename I = char>
	inline constexpr U pearson_hash(const T* data, size_t num = 1) {
		return iterable_hash<T, U, I>(data, [](I& r, const I* d) { r = r ^ *d; }, num);
	}
}