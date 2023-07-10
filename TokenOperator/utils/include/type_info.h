#pragma once
namespace utils {
	template<typename INNER, typename OUTER> constexpr inline
	size_t type_in_type_capasity(){
		return sizeof(OUTER) / sizeof(INNER);
	}
	template<typename INNER, typename OUTER> constexpr inline
	size_t type_in_type_wholes() {
		return sizeof(OUTER) % sizeof(INNER);
	}
}