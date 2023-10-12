#pragma once
#include "token/object.h"
namespace tokenoperator::dte_token::function {
	enum error_code : uint64_t {
		DTE_EC_OK = 0,	//OK

		DTE_EC_DATA_NULLPTR = 1,				//ERROR: can`t access memory (nullptr)
		DTE_EC_DATA_ACCESS_VIOLATION = 2,		//ERROR: can`t access memory properly
		DTE_EC_DATA_COLLISION = 3,				//ERROR: can`t add object because it will cause collision

		DTE_EC_LOW_ARG_NUM = 4,					//ERROR: function got args less than expected

		DTE_EC_STREAM_EXEC_ALIVE_THREAD = 5,	//ERROR: can`t execute alive thread
		DTE_EC_STREAM_FORCE_THREAD_STOP = 6		//ERROR: thread was forced to be ternimated
	};
}