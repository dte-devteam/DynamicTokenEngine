#pragma once
#include "token/object.h"
namespace tokenoperator::dte_token::function {
	enum error_code : uint64_t {
		DTE_EC_OK = 0,	//OK

		DTE_EC_DATA_NULLPTR = 0,				//ERROR: can`t access memory (nullptr)
		DTE_EC_DATA_ACCESS_VIOLATION = 0,		//ERROR: can`t access memory properly
		DTE_EC_DATA_COLLISION = 0,				//ERROR: can`t add object because it will cause collision

		DTE_EC_LOW_ARG_NUM = 0,					//ERROR: function got args less than expected

		DTE_EC_STREAM_EXEC_ALIVE_THREAD = 0,	//ERROR: can`t execute alive thread
		DTE_EC_STREAM_FORCE_THREAD_STOP = 0		//ERROR: thread was forced to be ternimated
	};
}