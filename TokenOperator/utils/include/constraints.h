#pragma once
#include <type_traits>
namespace dte_utils {
	//concepts
	template<typename U, typename T>
	concept copy_constructible = std::is_constructible_v<T, const U&>;
	template<typename U, typename T>
	concept move_constructible = std::is_constructible_v<T, U&&>;
	template<typename U, typename T>
	concept copyable_and_movable = copy_constructible<U, T> && move_constructible<U, T>;
	template<typename U, typename T>
	concept copyable_or_movable = copy_constructible<U, T> || move_constructible<U, T>;
}