#pragma once
#include "module/include/module.h"
namespace module_operator {
	struct module_unit {
		bool init_status;
		bool stack_status;
		module::module module_intance;
	};
}