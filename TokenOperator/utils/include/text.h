#pragma once
namespace dte_utils {
	inline char constexpr_strcmp(const char* str1, const char* str2) {
		while (*str1 == *str2 && *str1) {
			++str1;
			++str2;
		}
		return *str1 - *str2;
	}
	inline size_t constexpr_strlen(const char* str) {
		const char* i = str;
		while (*i) {
			++i;
		}
		return i - str;
	}
	char* constexpr_strcpy(const char* str) {
		size_t size = constexpr_strlen(str);
		char* r = new char[++size];
		char* i = r + size;
		str += size;
		while (i != r) {
			*--i = *--str;
		}
		return r;
	}
	size_t constexpr_substr_num(const char* str, const char* substr) {
		size_t num = 0;
		const char* i;
		while (*str) {
			i = substr;
			while (*str == *i && *i) {
				++str;
				++i;
			}
			if (!*i) {
				++num;
			}
			++str;
		}
		return num;
	}
	//to do
	//size_t constexpr_regexp_num(const char* str, const char* regexp) {
	//	size_t num = 0;
	//}
}