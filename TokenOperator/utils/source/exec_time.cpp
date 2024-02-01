#include "../include/exec_time.h"
using namespace dte_utils;
exec_time::exec_time() {
	creation_time = start_time = clock();
}
clock_t exec_time::get_creation_time() {
	return creation_time;
}
clock_t exec_time::get_start_time() {
	return start_time;
}
clock_t exec_time::get_dt() {
	clock_t end_time = clock();
	clock_t dt = end_time - start_time;
	start_time = end_time;
	return dt;
}
clock_t exec_time::set_start_time() {
	start_time = clock();
	return start_time;
}