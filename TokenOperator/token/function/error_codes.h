#pragma once
#include "token/object.h"
namespace tokenoperator::dte_token::function {
	enum error_code : uint64_t {
		DTE_EC_OK = 0,	//OK

		DTE_DATA_NULLPTR = 0,					//ERROR: can`t access memory (nullptr)

		DTE_EC_STREAM_EXEC_ALIVE_THREAD = 0,	//ERROR: can`t execute alive thread
		DTE_EC_STREAM_FORCE_THREAD_STOP = 0		//ERROR: thread was forced to be ternimated
	};
}