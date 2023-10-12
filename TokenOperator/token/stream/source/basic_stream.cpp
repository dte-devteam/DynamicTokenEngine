#include "../include/basic_stream.h"
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::stream;
basic_stream::basic_stream(data::smart_pointer<object> function, uint64_t ID) : basic_function(ID), function(function), thread(std::thread()), alive(false), errorcode(0) {}
basic_stream::~basic_stream() {
	killstream();
}
void basic_stream::execute(const basic_stream& caller, const bf_args& argument_pointer, bool forced) {
	ENTER_STACK
	//to do collect caller data
	if (isalive()) {
		RAISE_ERROR(DTE_EC_STREAM_EXEC_ALIVE_THREAD)
	}
	else if (function.get_pointer()) {
		alive.store(true);
		//to do form new bf_args for this thread by caller bf_args (can`t just share - may cause UB)
		callstack = new std::stack<uint64_t>();
		thread = std::thread(
			[this, argument_pointer, forced] {
				((basic_function*)function.get_pointer())->execute(*this, argument_pointer, forced);
				this->errorcode = 0;	//temp, should send error (to do)
				this->free_stream_data();
				this->alive.store(false);
			}
		);
	}
	else {
		RAISE_ERROR(DTE_EC_DATA_NULLPTR)
	}
	EXIT_STACK
}
uint64_t basic_stream::getfunctionID() const {
	return function.get_pointer() ? function->getID() : 0;
}
void basic_stream::killstream() {
	errorcode = DTE_EC_STREAM_FORCE_THREAD_STOP;
	joinstream();
}
void basic_stream::joinstream() {
	if (thread.joinable()) {
		thread.join();
	}
}
bool basic_stream::isalive() {
	return alive.load();
}
void basic_stream::free_stream_data() {
	//to do (remove all smart_pointer<object>)
}