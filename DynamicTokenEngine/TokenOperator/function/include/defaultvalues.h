#pragma once
#include "function/include/defaultvalues.h"
#include "token_data.h"
namespace defaultvalues {
	//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
	static size_t POINTER_SIZE = sizeof(void*);


	static defaultvaluescontainer defaultconstants = defaultvaluescontainer({
		new defaultvalue(sizeof(void*), token_data::token_name_to_id(L"NULL_PTR")),
		new defaultvalue(sizeof(unsigned long long), token_data::token_name_to_id(L"ULL_ZERO")),
		new defaultvalue(sizeof(unsigned int), token_data::token_name_to_id(L"UINT_ZERO")),
		new defaultvalue(sizeof(unsigned int), token_data::token_name_to_id(L"POINTER_SIZE"), &POINTER_SIZE)
	});
}