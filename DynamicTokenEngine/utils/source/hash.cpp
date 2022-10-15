#include "../include/hash.h"
namespace utils {
	namespace hash {
		uint32_t pirson_hash_with_rol(std::wstring string) {
			uint32_t hash = 0;
			uint32_t secondhash = 0;
			bool order = true;
			for (wchar_t c : string) {
				if (order) {
					hash ^= c;
				}
				else {
					secondhash ^= c;
				}
				order = !order;
			}
			secondhash = secondhash << 16;
			return hash | secondhash;
		}
	}
}