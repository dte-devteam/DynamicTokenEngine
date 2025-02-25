#pragma once
#include <type_traits>
namespace dte_utils {
	//concepts
	template<typename T, typename U>
	concept castable = requires (T t, U u) {
		u = static_cast<U>(t);
	};
}