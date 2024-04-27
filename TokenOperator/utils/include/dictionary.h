#pragma once
#include "dynamic_array.h"
#include <utility>
namespace dte_utils {
	template<typename K, typename V>
	struct dictionary : dynamic_array<std::pair<K, V>> {
		using dynamic_array::dynamic_array;
		V* operator[](const K& key) {
			return find([&key](const std::pair<K, V>& iter) { return key == iter.first; });
		}
		V* operator[](K&& key) {
			return find([&key](const std::pair<K, V>& iter) { return key == iter.first; });
		}
	};
}