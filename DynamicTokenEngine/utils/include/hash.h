#pragma once
#include <stdint.h>
#include <cvt/wstring>
namespace utils {
	namespace hash {
		uint32_t pirson_hash_with_rol(std::wstring string);
	}
}