#include "../include/module_requirement.h"
namespace module {
	module_requirement::module_requirement(std::wstring dllname, module_version minversion, module_version maxversion) : dllname(dllname), versions{ minversion, maxversion } {}
	std::wstring module_requirement::getname() {
		return dllname;
	}
	module_version module_requirement::getminversion() {
		return versions[0];
	}
	module_version module_requirement::getmaxversion() {
		return versions[1];
	}
}