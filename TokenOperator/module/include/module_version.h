#pragma once
#include "token/object.h"
namespace tokenoperator::dte_module {
	#define MODULE_VERSION_ELEMENTS 4
	#define MAX_MODULE_VERSION 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
	struct module_version : dte_token::object {
		public:
			module_version(uint64_t ID = 0, uint16_t v0 = 0, uint16_t v1 = 0, uint16_t v2 = 0, uint16_t v3 = 0);
		protected:
			uint16_t version_numbers[MODULE_VERSION_ELEMENTS];
	};
}