#pragma once
#include "token/memory/include/external_interaction.h"
namespace memory {
	namespace external {
		static importdllstructure importdll {
			0,	//name
			{	//defaultvalues
				nullptr,	//LPCWSTR of dllname
				nullptr		//where dll pointer should be written
			}
		};
		static getprocaddressstructure getprocaddress {
			0,	//name
			{	//defaultvalues
				nullptr,	//dll entry pointer
				nullptr,	//where proc pointer should be written
				nullptr		//LPCSTR of proc name
			}
		};
	}
}