#pragma once
#include <stdint.h>
#include <cvt/wstring>
namespace token_data {
	constexpr inline uint64_t token_name_to_id(std::wstring string) {
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
	constexpr inline uint32_t token_type_to_id(std::wstring string) {
		wchar_t hash = 0;
		for (wchar_t c : string) {
			hash ^= c;
		}
		return hash;
	}
}