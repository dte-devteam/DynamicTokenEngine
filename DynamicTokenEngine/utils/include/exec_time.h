#pragma once
#include <iostream>
class exec_time {
	public:
		exec_time(){}
		~exec_time(){}
		void log() {
			clock_t t = clock();
			std::cout << "exec time: " << (t - dt) / 1000.0 << "ms, total: " << (t - tdt) / 1000.0 << "ms" << std::endl;
			dt = t;
		}
	private:
		clock_t dt = clock();
		clock_t tdt = dt;
};