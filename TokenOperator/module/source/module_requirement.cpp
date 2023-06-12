#include "../include/module_requirement.h"
using namespace tokenoperator::dte_module;
module_requirement::module_requirement(std::wstring dllname, module_version minversion, module_version maxversion, uint64_t ID) : value<module_version[2]>(ID), dllname(dllname) {
	v[0] = minversion;
	v[1] = maxversion;
}