#pragma once
#include "token/data/include/value.h"
namespace tokenoperator::dte_module {
	#define MAX_MODULE_VERSION 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	struct module_version : dte_token::data::value<uint16_t[4]> {
		public:
			module_version(uint64_t ID = 0, uint16_t v0 = 0, uint16_t v1 = 0, uint16_t v2 = 0, uint16_t v3 = 0);
	};
}