#include "../include/module_requirement.h"
namespace module {
	module_requirement::module_requirement(std::wstring dllname, module_version minversion, bool critical) : dllname(dllname), minversion(minversion), critical(critical) {}
	std::wstring module_requirement::getname() {
		return dllname;
	}
	module_version module_requirement::getminversion() {
		return minversion;
	}
	bool module_requirement::iscritical() {
		return critical;
	}
}