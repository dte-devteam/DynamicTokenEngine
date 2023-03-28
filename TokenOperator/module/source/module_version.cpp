#include "../include/module_version.h"
namespace module {
	bool operator >(module_version& ver1, module_version& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] > ver2.versionnumbers[i]) {
				return true;
			}
		}
		return false;
	}
	bool operator ==(module_version& ver1, module_version& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] != ver2.versionnumbers[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator >(module_version&& ver1, module_version&& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] > ver2.versionnumbers[i]) {
				return true;
			}
		}
		return false;
	}
	bool operator ==(module_version&& ver1, module_version&& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] != ver2.versionnumbers[i]) {
				return false;
			}
		}
		return true;
	}
}