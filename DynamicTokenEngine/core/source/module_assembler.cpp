#include "../include/module_assembler.h"
using namespace dte_module;
using namespace dte_token;
using namespace dte_core;
object* module_assembler::get_object(const path& p) {
	if (p.get_used_size() < 2) {
		return nullptr;
	}
	size_t name = p[0].ID;
	module_unit* mu = module_assembler::get_instance().modules.find(
		[name](const module_unit& i) {
			return i.instance->virtual_name == name;
		}
	);
	if (mu) {
		name = p[1].ID;
		object_handler* oh = mu->instance->module_static_data.find(
			[](const object_handler& i) {
				return i.ID == 0;
			}
		);
		if (oh) {
			return p.get_object(*oh, 2, p.get_used_size() - 2);
		}
	}
	return nullptr;
}
void module_assembler::register_module(module_instance* mi) {
	if (type_assembler::set_min_reserved_size(mi->module_static_types.get_used_size())) {
		for (module_unit& mu : module_assembler::get_instance().modules) {
			for (type_handler& th : mu.instance->module_static_types) {
				type_assembler::register_type(th);
			}
		}
	}
	for (type_handler& th : mi->module_static_types) {
		type_assembler::register_type(th);
	}
	module_assembler::get_instance().modules.push_back({ 0,  {}, mi });
}