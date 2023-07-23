#include "../include/stream.h"
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::stream;
stream::stream(data::smart_pointer<object> function, uint64_t ID) : basic_function(ID), function(function), thread(std::thread()), alive(false), generatederrorcode(0) {
	stream_errorcodepointer = &generatederrorcode;
}
stream::~stream() {
	killstream();
}
void stream::execute(bf_args* argumentspointer, uint64_t* errorcodepointer, bool forced, stack* callstack, stream* caller) {
	USE_STACK
	//to do collect caller data
	if (isalive()) {
		if (errorcodepointer) {
			*errorcodepointer = DTE_EC_STREAM_EXEC_ALIVE_THREAD;
		}
	}
	else if (function.get_pointer()) {
		alive.store(true);
		//to do form new bf_args for this thread by caller bf_args (can`t just share - may cause UB)
		stream_errorcodepointer = errorcodepointer ? errorcodepointer : &generatederrorcode;
		thread = std::thread(
			[argumentspointer, forced, callstack, this] {
				((basic_function*)function.get_pointer())->execute(argumentspointer, this->stream_errorcodepointer, forced, callstack, this);
				this->generatederrorcode = 0;
				this->free_stream_data();
				this->alive.store(false);
			}
		);
	}
	else if (errorcodepointer) {
		*errorcodepointer = DTE_DATA_NULLPTR;
	}
}
uint64_t stream::getfunctionID() const {
	return function.get_pointer() ? function->getID() : 0;
}
void stream::killstream() {
	*stream_errorcodepointer = DTE_EC_STREAM_FORCE_THREAD_STOP;
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