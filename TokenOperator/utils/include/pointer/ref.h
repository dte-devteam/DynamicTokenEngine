#pragma once
//#include <type_traits>
#include "function.h"
namespace dte_utils {
	template<typename T>
	using ref_pointer = std::conditional_t<
		return_type_v<T>,
		T,
		std::conditional_t<
			std::is_array_v<T>,
			std::decay_t<T>,
			T*
		>
	>;
	template<typename T>
	inline constexpr bool ref_instantiable = !(
		std::is_void_v<T>	||	//can`t return void as object
		std::is_array_v<T>	||	//can`t use array as single object
		return_type_v<T>	//can`t return function as object
	);
	template<typename T>
	struct ref {
		ref_pointer<T> instance;
		size_t weak_owners;
		size_t strong_owners;
		ref(ref_pointer<T> instance = nullptr) noexcept : instance(instance), weak_owners(0), strong_owners(0) {}
	};
	#define REF_ASSIGN_LIMITS																											\
		static_assert(																													\
			std::is_array_v<T> == std::is_array_v<U> &&																					\
			(																															\
				std::is_same_v<ref_pointer<T>, ref_pointer<U>> ||																		\
				std::is_base_of_v<T, U>																									\
			)																															\
			, "ref: array pointer can be set only by array and vice versa\nnon-array instance can be set by same or parent instance"	\
		);
}