#include "../include/stream.h"
namespace memory {
	namespace stream {
		bool absolutestreamrights::getkillrights() {
			return killstream;
		}
		bool absolutestreamrights::getsemaphorerights() {
			return semaphore;
		}

		stream::stream(basicfunction* function, uint64_t id, stream* caller) : basicfunction(id), function(function), caller(caller) {
			if (!caller) {
				caller = this;
			}
		}
		stream::~stream() {
			for (stream* s : childstreams) {
				killstream(this, true);
			}
			delete rights;
		}
		void stream::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
			if (function) {
				thread = new std::thread(&basicfunction::execute, function, argumentspointer, errorcodepointer, forced);
			}
			else if (errorcodepointer) {
				*errorcodepointer = 7658;	//change error code (to do): cant execute nullptr of function
			}
		}
		void stream::killstream(stream* caller, bool shouldjoin) {
			if (thread) {
				if (caller) {
					if (caller->getid() == this->caller->getid()) {
						goto killstream;
					}
					else if (caller->rights->getkillrights()) {
						goto killstream;
					}
					return;
				}
				killstream:
				if (thread) {
					if (thread->joinable() && shouldjoin) {
						thread->join();
					}
				}
				delete this;
			}
		}

		bool stream::isalive() {
			if (thread) {
				return std::thread::id() == thread->get_id();	//may be wrong!!! (check)
			}
			return false;
		}
		bool stream::iswaiting() {
			if (thread) {
				//get semaphore value (to do)
			}
			return false;
		}
	}
}