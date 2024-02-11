#pragma once
#include "module/include/module_version.h"
#include "module/include/module_instance.h"
#include "target_architecture.h"
#include <libloaderapi.h>
namespace dte_core {
	struct module_unit {
		HMODULE hmodule;
		dte_module::module_version vesrion;
		dte_module::module_instance* instance;
		~module_unit() {
			FreeLibrary(hmodule);
		}
	};
}