#pragma once
#include <vector>
#include "../../function/include/functionfactory.h"
#include "external_interaction.h"
using namespace functionfactory;
namespace memory {
	namespace function {
		struct importfunctionstruct : typedfunction {
			using typedfunction::typedfunction;
		};
		struct createfunctionstruct : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {}
		};
		struct functionloaderstruct : muxfunction {
			using muxfunction::muxfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {}
		};
		//constances
		static LPCSTR dllfunctionloadername = "getfunctions";
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
						{0, false},
						{1, false},
						{(size_t)dllfunctionloadername, true}
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
		static std::vector<basicfunction*> functions;
		//в процессе инициации/добавления/поиска новых функции нужно будет делить вектор функций на куски и обрабатывать это параллельно
		//чтобы при поиске функции find_if не занимала слишком много времени
	}
}