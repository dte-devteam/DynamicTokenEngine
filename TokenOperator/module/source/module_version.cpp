#include "../include/module_version.h"
using namespace tokenoperator::dte_module;
module_version::module_version(uint64_t ID, uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3) : dte_token::data::value<std::array<uint16_t, 4>>(ID) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}
module_version::module_version(const module_version& mv) : module_version(mv.ID, mv.v[0], mv.v[1], mv.v[2], mv.v[3]) {}