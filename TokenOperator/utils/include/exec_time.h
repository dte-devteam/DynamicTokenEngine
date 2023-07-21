#pragma once
#include "token/object.h"
#include <ctime>
//#include <cstdarg>
namespace utils {
	struct exec_time : tokenoperator::dte_token::object {
		public:
			exec_time(uint64_t ID = 0);
			clock_t get_creation_time();
			clock_t get_start_time();
			clock_t get_dt();
			clock_t set_start_time();
		protected:
			clock_t creation_time, start_time;
	};
}