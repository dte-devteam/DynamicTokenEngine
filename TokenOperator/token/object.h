#pragma once
#include "utils/include/hash.h"
#include <stdint.h>
#include <xstring>
namespace tokenoperator::dte_token {
#define TOKEN_NAME(lpwstr) token_name(lpwstr, std::char_traits<wchar_t>::length(lpwstr))
	struct object {
		public:
			object(uint64_t ID) : ID(ID){}
			virtual ~object() {}
			uint64_t getID() const {
				return ID; 
			}
		protected:
			uint64_t ID;
	};
	constexpr inline uint64_t token_name(wchar_t* wstr, size_t wstr_len) {
		return utils::pearson_hash<wchar_t, uint64_t>(wstr, wstr_len);
	}
}