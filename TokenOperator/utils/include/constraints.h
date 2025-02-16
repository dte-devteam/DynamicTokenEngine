#pragma once
namespace dte_utils {
	template<typename T, typename U>
	concept Castable = requires (T t, U u) { u = static_cast<U>(t); };
}