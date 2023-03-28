#pragma once
#include <stdint.h>
namespace module {
	#define MODULE_VERSION_ELEMENTS 4
	class module_version {
		friend bool operator >(module_version& ver1, module_version& ver2);
		friend bool operator ==(module_version& ver1, module_version& ver2);
		friend bool operator >(module_version&& ver1, module_version&& ver2);
		friend bool operator ==(module_version&& ver1, module_version&& ver2);
		public:
			constexpr module_version(uint16_t v0 = 0, uint16_t v1 = 0, uint16_t v2 = 0, uint16_t v3 = 0) : versionnumbers{ v0, v1, v2, v3 } {}
			constexpr uint16_t* getversion() {
				return versionnumbers;
			}
		protected:
			uint16_t versionnumbers[MODULE_VERSION_ELEMENTS];
	};
}