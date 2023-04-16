#include "../include/stream.h"
namespace stream {
	stream::stream(basicfunction* function, uint64_t id, stream* caller) : basicfunction(id), function(function), caller(caller) {
		//generate rights(to do)
		rights = new absolutestreamrights();
	}
	stream::~stream() {
		killstream(this);
		delete rights;
		delete generatederrorcodepointer;
	}
	void stream::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		if (alive.load()) {
			if (errorcodepointer) {
				*errorcodepointer = 9090;	//change error code (to do): cant execute alive thread
			}
			return;
		}
		if (function) {
			if (thread.joinable()) {
				thread.join();
			}
			alive.store(true);
			if (errorcodepointer) {
				sharederrorcodepointer = errorcodepointer;
			}
			else {
				*generatederrorcodepointer = 0;
				sharederrorcodepointer = generatederrorcodepointer;
			}
			thread = std::thread(
				[this, argumentspointer, forced] {
					function->execute(argumentspointer, sharederrorcodepointer, forced, this);
					alive.store(false);
				}
			);
		}
		else if (errorcodepointer) {
			*errorcodepointer = 7658;	//change error code (to do): cant execute nullptr of function
		}
	}
	bool stream::killstream(stream* caller) {
		if (alive.load()) {
			if (caller) {
				if (this->id == caller->id) {
					return false;
				}
				if (caller->rights->getkillrights()) {
					goto killstream;
				}
				if (this->caller) {
					if (caller->id == this->caller->id) {
						goto killstream;
					}
				}
			}
			return false;
			killstream:
			for (stream* s : childstreams) {
				s->killstream(this);
			}
			*sharederrorcodepointer = data::errorvalues::FORCE_STOP;	//change, maybe temprorary value
			alive.wait(true);
			//unregister every used iteretor (to do)
			//for (void* i : iterators) {
			//	((object::iterator*)i)->unregisterobject(this);
			//}
			iterators.clear();
		}
		return true;
	}
	void stream::joinstream(stream* caller) {
		if (alive.load()) {
			if (!caller) {
				return;
			}
			if (caller->id == this->id) {
				return;
			}
			if (thread.joinable()) {
				return thread.join();	//if will be called from few thread will lead data race (to do, mutex?)
			}
		}
	}
	bool stream::isalive() {
		return alive;
	}
	bool stream::setfunction(basicfunction* func) {
		if (alive.load() || !func) {
			return false;
		}
		function = func;
		return true;
	}
	uint64_t stream::getfunctionid() {
		if (function) {
			return function->getid();
		}
		return NULL;
	}
}