#include "../include/function_requirement.h"
#include "token_data.h"
namespace module {
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
}