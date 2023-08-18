#include "../include/stream.h"
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::stream;
stream::stream(data::smart_pointer<object> function, uint64_t ID) : basic_function(ID), function(function), thread(std::thread()), alive(false), errorcode(0) {}
stream::~stream() {
	killstream();
}
void stream::execute(stream* caller, bf_args* argument_pointer, bool forced) {
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
				((basic_function*)function.get_pointer())->execute(this, argument_pointer, forced);
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
uint64_t stream::getfunctionID() const {
	return function.get_pointer() ? function->getID() : 0;
}
void stream::killstream() {
	errorcode = DTE_EC_STREAM_FORCE_THREAD_STOP;
	joinstream();
}
void stream::joinstream() {
	if (thread.joinable()) {
		thread.join();
	}
}
bool stream::isalive() {
	return alive.load();
}
void stream::free_stream_data() {
	//to do (remove all smart_pointer<object>)
}