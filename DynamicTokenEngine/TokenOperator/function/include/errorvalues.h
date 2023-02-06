#pragma once
#include "function/include/errorvalues.h"
namespace functionfactory {
	namespace errorvalues {
		//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
		static errorcode geterrorcode{
			token_data::token_name_to_id(L"geterrorcode") //name
		};
	}
}