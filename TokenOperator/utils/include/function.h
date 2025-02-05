#pragma once
#include <type_traits>
namespace dte_utils {
	//Return false if T is not function pointer.
	template<typename T>
	struct return_type : std::false_type {};
	template<typename R, typename ...Args>
	struct return_type<R(*)(Args...)> : std::true_type {
		using type = R;
	};
	template<typename T>
	using return_type_t = typename return_type<T>::type;
	template<typename T>
	inline constexpr bool return_type_v = return_type<T>::value;
}