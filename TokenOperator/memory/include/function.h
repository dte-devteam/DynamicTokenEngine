#pragma once
#include "function/include/functionfactory.h"
#include "external_interaction.h"
namespace memory {
	namespace function {
		struct importfunctionstruct : functionfactory::typedfunction {
			using functionfactory::typedfunction::typedfunction;
		};
		struct createfunctionstruct : functionfactory::basicfunction {
			using functionfactory::basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
		};
		struct functionloaderstruct : functionfactory::muxfunction {
			using functionfactory::muxfunction::muxfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {}
		};

		//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
		//instances
		static importfunctionstruct importfunction {
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
		static createfunctionstruct createfunction {
			0,	//name (change)
			{	//default values
				nullptr,	//where basicfunction* should be writen
				nullptr,	//function name (uint64_t*)
				nullptr,	//default values (vector<void*>*)
				nullptr,	//subfunctions` pointers (vector<basicfunction*>)
				nullptr,	//args indices (vector<size_t>*)
				nullptr		//args indices mode (vector<bool>*)
			}
		};
		static functionloaderstruct functionloader {
			//to do (must create f() from other functions)
		};
		static std::vector<functionfactory::basicfunction*> functions;
		//в процессе инициации/добавления/поиска новых функции нужно будет делить вектор функций на куски и обрабатывать это параллельно
		//чтобы при поиске функции find_if не занимала слишком много времени
	}
}