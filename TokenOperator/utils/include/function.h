#pragma once
namespace dte_utils {
	template<typename T>
	struct return_type {};
	template<typename R, typename ...Args>
	struct return_type<R(*)(Args...)> {
		using type = R;
	};
	template<typename T>
	using return_type_t = typename return_type<T>::type;
}