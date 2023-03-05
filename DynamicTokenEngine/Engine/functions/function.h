#pragma once
#include "memory/include/function.h"
#include "external_interaction.h"
namespace memory {
	namespace function {
		static importfunctionstruct importfunction{
			0,	//name (change)
			{	//default values
				nullptr,	//module path (LPCWSTR)
				nullptr		//where dll pointer should be written (void*)
			},
			{	//callings
				{
					&external::importdll,
					{
						{0, false},
						{1, false}
					}
				},
				{
					&external::getprocaddress,
					{
						{1, false},
						{1, false},
						{(size_t)"getfunctions", true}
					}
				}
			},
			{	//valuetypes
				{
					0	//LPCWSTR
				},
				{
					0	//void*
				}
			}
		};
	}
}