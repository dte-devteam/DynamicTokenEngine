#pragma once
#include <ctime>
//#include <cstdarg>
namespace dte_utils {
	struct exec_time {
		public:
			exec_time();
			clock_t get_creation_time();
			clock_t get_start_time();
			clock_t get_dt();
			clock_t set_start_time();
		protected:
			clock_t creation_time, start_time;
	};
}