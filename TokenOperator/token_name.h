#pragma once
#include <stdint.h>
#include <cvt/wstring>
namespace token_name {
	constexpr uint64_t token_name_to_id(std::wstring string) {
		wchar_t hash_0 = 0;
		wchar_t hash_1 = 0;
		bool order = true;
		for (wchar_t c : string) {
			if (order) {
				hash_0 ^= c;
			}
			else {
				hash_1 ^= c;
			}
			order = !order;
		}
		uint64_t hash = hash_1;
		return (hash << 32) | hash_0;
	}
}