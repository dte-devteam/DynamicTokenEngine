#include "../include/module_source.h"
using namespace tokenoperator::dte_module;
using namespace tokenoperator::dte_token::data;
module_source::module_source(const module_source& ms) : value<std::pair<smart_pointer<object>, bool>>(ms.ID), init_status{ ms.init_status[0], ms.init_status[1] }, requirement_num(ms.requirement_num), requirements(new module_source_requirement[ms.requirement_num]), path_to_set(ms.path_to_set) {
	v = ms.v;
	size_t i = requirement_num;
	while (i) {
		requirements[i] = ms.requirements[--i];
	}
}
bool module_source::get_init_status() {
	return init_status[0];
}
bool module_source::get_stack_status() {
	return init_status[1];
}
size_t module_source::get_requirement_num() {
	return requirement_num;
}
module_source_requirement& module_source::operator[](size_t i) {
	return requirements[i];
}
scope_path* module_source::get_path_to_set() {
	return &path_to_set;
}