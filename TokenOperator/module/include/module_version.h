#pragma once
#include <stdint.h>
#define MAX_MODULE_VERSION 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
namespace dte_module {
	struct module_version {
		uint16_t numbers[4];
		bool set_version_to_file(const wchar_t* path);
	};
}