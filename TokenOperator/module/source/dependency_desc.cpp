#include "../include/dependency_desc.h"
#include "token_data.h"
namespace dependency_desc {
	bool operator >(module_version& ver1, module_version& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] > ver2.versionnumbers[i]) {
				return true;
			}
		}
		return false;
	}
	bool operator ==(module_version& ver1, module_version& ver2) {
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] != ver2.versionnumbers[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator >(module_version&& ver1, module_version&& ver2) { 
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] > ver2.versionnumbers[i]) {
				return true;
			}
		}
		return false;
	}
	bool operator ==(module_version&& ver1, module_version&& ver2) { 
		for (size_t i = 0; i < MODULE_VERSION_ELEMENTS; i++) {
			if (ver1.versionnumbers[i] != ver2.versionnumbers[i]) {
				return false;
			}
		}
		return true;
	}
	module_requirement::module_requirement(std::wstring dllname, module_version minversion, bool critical) : dllname(dllname), minversion(minversion), critical(critical){}
	std::wstring module_requirement::getname() {
		return dllname;
	}
	module_version module_requirement::getminversion() {
		return minversion;
	}
	bool module_requirement::iscritical() {
		return critical;
	}
	function_requirement::function_requirement(uint64_t name, size_t index, desc_type desc_type) : name(name), index(index), type(desc_type){}
	function_requirement::function_requirement(std::wstring name, size_t index, desc_type desc_type) : function_requirement(token_data::token_name_to_id(name), index, desc_type){}
	uint64_t function_requirement::getname() {
		return name;
	}
	size_t function_requirement::getindex() {
		return index;
	}
	desc_type function_requirement::getdesctype() {
		return type;
	}
	function_data::function_data(functionfactory::basicfunction* function, std::vector<function_requirement> requirements) : function(function), requirements(requirements), init_status(!requirements.size()){}
}