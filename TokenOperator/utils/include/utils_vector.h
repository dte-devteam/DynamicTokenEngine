#pragma once
namespace utils {
	namespace vector {
		template <class T, class F>
		T find_if_last(T begin, T end, F function) {
			for (T i = begin; i != end; ++i) {
				if (!function(i)) {
					return i - 1;
				}
			}
			return end;
		}
	}
}