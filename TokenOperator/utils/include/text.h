#pragma once
namespace dte_utils {
	constexpr inline char constexpr_strcmp(const char* str1, const char* str2) {
		char d = *str1 - *str2;
		while (!(d || *str1 == '\0')) {
			++str1;
			++str2;
		}
		return d;
	}
	constexpr inline size_t constexpr_strlen(const char* str) {
		const char* i = str;
		while (*i != '\0') {
			++i;
		}
		return i - str;
	}
	constexpr char* constexpr_strcpy(const char* str) {
		size_t size = constexpr_strlen(str);
		char* r = new char[++size];
		char* i = r + size;
		str += size;
		while (i != r) {
			*--i = *--str;
		}
		return r;
	}
}