#include "../include/type_assembler.h"
using namespace dte_utils;
using namespace dte_token;
using namespace dte_core;
void type_assembler::init(const dynamic_array<type>& array, size_t reserve) {
	types = { array, reserve };
}
type* type_assembler::get_type(size_t virtual_type) {
	return types.find(
		[virtual_type](const type& t) {
			return t.virtual_type == virtual_type; 
		}
	);
}
type* type_assembler::get_type(const char* name) {
	return types.find(
		[name](const type& t) {
			return !constexpr_strcmp(t.name, name); 
		}
	);
}
void type_assembler::register_type(type& type_to_add) {
	type* t = type_assembler::get_instance().get_type(type_to_add.name);
	if (t) {
		type_to_add.virtual_type = t->virtual_type;
	}
	else {
		type_to_add.virtual_type = type_assembler::get_instance().get_free_vir_type();
		t = new type(type_to_add);
		type_assembler::get_instance().types.push_back(*t);
	}
}
size_t type_assembler::get_free_vir_type() {
	return types.us;
}