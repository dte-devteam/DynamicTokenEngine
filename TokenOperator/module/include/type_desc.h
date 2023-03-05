#pragma once
#include <stdint.h>
#include <cvt/wstring>
#include "token_data.h"
namespace type_desc {
	class typedesc {
		public:
			typedesc(uint32_t type = 0, size_t size = 0);
			uint32_t gettype();
			size_t getsize();
		private:
			uint32_t type;
			size_t size;
	};
}