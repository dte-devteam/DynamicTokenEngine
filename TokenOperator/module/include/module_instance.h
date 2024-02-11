#pragma once
#include "token/include/object.h"
#include "utils/include/dynamic_array.h"
namespace dte_module {
	//function for (re)initiation (to do)
	struct module_instance {
		size_t												virtual_name;
		dte_utils::dynamic_array<dte_token::type_handler>	module_static_types;	//required or provided types
		dte_utils::dynamic_array<dte_token::object_handler>	module_static_data;		//provided static data
		dte_token::global_get_object ggo;
	};
}