#include "../include/module_source_requirement.h"
using namespace tokenoperator::dte_module;
using namespace tokenoperator::dte_token::data;
module_source_requirement::module_source_requirement(void* target, scope_path source, bool iscritical, uint64_t ID) : value<void*>(ID), source(source), critical(iscritical) {
	v = target;
}
module_source_requirement::module_source_requirement(const module_source_requirement& msr) : value<void*>(msr.ID), source(msr.source), critical(msr.critical) {
	v = msr.v;
}
scope_path module_source_requirement::get_source() {
	return source;
}
bool module_source_requirement::iscritical() {
	return critical;
}