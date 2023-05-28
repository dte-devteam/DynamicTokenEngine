#include "../include/module_version.h"
using namespace tokenoperator::dte_module;
module_version::module_version(uint64_t ID, uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3) : dte_token::object(ID), version_numbers{ v0, v1, v2, v3 } {}