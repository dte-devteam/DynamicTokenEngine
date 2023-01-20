#pragma once
#include <iostream>
#include "functionfactory.h"
#include "../../token_name.h"
namespace functionfactory {
	namespace errorvalues {
		enum errorvalues {
			NO_ERROR_NO_HANDLER,
			NO_ERROR_HANDLER,
			NULLPTR,
			INDEX_OUT_RANGE
		};
		struct errorcode : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
			private:
				std::vector<const wchar_t*> errorvalues{
					L"NO ERROR HANDLER: OK",
					L"ERROR HANDLER: OK",
					L"NULL POINTER ERROR",
					L"INDEX OUT RANGE"
				};
		};
		static errorcode geterrorcode{
			token_name::token_name_to_id(L"geterrorcode") //name
		};
	}
}