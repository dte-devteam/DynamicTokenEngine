#include "../include/module_assembler.h"
using namespace dte_module;
using namespace dte_token;
using namespace dte_core;
object* module_assembler::get_object(const path& p) {
	if (p.ways.us < 2) {
		return nullptr;
	}
	size_t name = p.ways[0].ID;
	module_instance** mi = module_assembler::get_instance().modules.find(
		[name](module_instance* i) {
			return i->virtual_name == name;
		}
	);
	if (mi) {
		name = p.ways[1].ID;
		object_handler* oh = (*mi)->module_static_data.find(
			[](const object_handler& i) {
				return i.ID == 0;
			}
		);
		if (oh) {
			return p.get_object(*oh, 2, p.ways.us - 2);
		}
	}
	return nullptr;
}