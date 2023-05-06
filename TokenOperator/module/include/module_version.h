#pragma once
#include <stdint.h>
namespace module {
	#define MODULE_VERSION_ELEMENTS 4
	#define MIN_MODULE_VERSION module_version()
	#define MAX_MODULE_VERSION module_version(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF)
	class module_version {
		public:
			//operators
			constexpr bool operator >(module_version& ver) {
				return *((uint64_t*)versionnumbers) > *((uint64_t*)ver.versionnumbers);
			}
			constexpr bool operator >(module_version&& ver) {
				return *((uint64_t*)versionnumbers) > *((uint64_t*)ver.versionnumbers);
			}
			constexpr bool operator ==(module_version& ver) {
				return *((uint64_t*)versionnumbers) == *((uint64_t*)ver.versionnumbers);
			}
			constexpr bool operator ==(module_version&& ver) {
				return *((uint64_t*)versionnumbers) == *((uint64_t*)ver.versionnumbers);
			}
			constexpr bool operator >=(module_version& ver) {
				return *((uint64_t*)versionnumbers) >= *((uint64_t*)ver.versionnumbers);
			}
			constexpr bool operator >=(module_version&& ver) {
				return *((uint64_t*)versionnumbers) >= *((uint64_t*)ver.versionnumbers);
			}
			//class methods
			constexpr module_version(uint16_t v0 = 0, uint16_t v1 = 0, uint16_t v2 = 0, uint16_t v3 = 0) : versionnumbers{ v0, v1, v2, v3 } {}
			constexpr uint16_t* getversion() {
				return versionnumbers;
			}
			constexpr bool in_range(module_version& minversion, module_version& maxversion) {
				return *this >= minversion && maxversion >= *this;
			}
			constexpr bool in_range(module_version&& minversion, module_version& maxversion) {
				return *this >= minversion && maxversion >= *this;
			}
			constexpr bool in_range(module_version&& minversion, module_version&& maxversion) {
				return *this >= minversion && maxversion >= *this;
			}
		protected:
			uint16_t versionnumbers[MODULE_VERSION_ELEMENTS];
	};
}