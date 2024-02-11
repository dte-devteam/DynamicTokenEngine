#include "../include/type_assembler.h"
using namespace dte_utils;
using namespace dte_token;
using namespace dte_core;
void type_assembler::init(const dynamic_array<type_handler>& array, size_t reserve) {
	//types = { array, reserve };
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
void type_assembler::register_type(type_handler& type_to_add) {
	type* t = type_assembler::get_instance().get_type(type_to_add.name);
	if (t) {
		type_to_add.type_instance = t;
	}
	else {
		type_assembler::get_instance().types.emplace_back(constexpr_strcpy(type_to_add.name), type_assembler::get_instance().get_free_vir_type());
		type_to_add.type_instance = type_assembler::get_instance().types.back();
	}
}
size_t type_assembler::get_free_vir_type() {
	return types.get_used_size();
}
bool type_assembler::set_min_reserved_size(size_t reserved_size) {
	type_assembler& instance = type_assembler::get_instance();
	size_t ds = instance.types.get_allocated_size() - instance.types.get_used_size();
	if (ds < reserved_size) {
		instance.types.resize(reserved_size - ds);
		return true;
	}
	return false;
}