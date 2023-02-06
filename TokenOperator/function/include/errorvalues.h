#pragma once
#include <iostream>
#include "functionfactory.h"
#include "../../token_data.h"
namespace functionfactory {
	namespace errorvalues {
		enum errorvalues {
			NO_ERROR_NO_HANDLER,
			NO_ERROR_HANDLER,
			FORCE_STOP,
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
					L"FROCED STOP",
					L"NULL POINTER ERROR",
					L"INDEX OUT RANGE"
				};
		};
	}
}