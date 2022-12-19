#include "../include/stream.h"
#include "../include/object.h"
namespace memory {
	namespace stream {
		absolutestreamrights::absolutestreamrights(bool killstreamrights, bool semaphorerights, bool joinrights, bool memoryrights) : kill(killstreamrights), semaphore(semaphorerights), join(joinrights), memoryrights(memoryrights) {
			join = true; //temp, for testing
			kill = true; //temp, for testing
		}
		bool absolutestreamrights::getkillrights() {
			return kill;
		}
		bool absolutestreamrights::getsemaphorerights() {
			return semaphore;
		}
		bool absolutestreamrights::getjoinrights() {
			return join;
		}
		bool absolutestreamrights::getmemoryrights() {
			return memoryrights;
		}

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
			if (alive) {
				if (errorcodepointer) {
					*errorcodepointer = 9090;	//change error code (to do): cant execute alive thread
				}
				return;
			}
			if (function) {
				if (thread.joinable()) {
					thread.join();
				}
				alive = true;
				if (errorcodepointer) {
					sharederrorcodepointer = errorcodepointer;
				}
				else {
					*generatederrorcodepointer = 0;
					sharederrorcodepointer = generatederrorcodepointer;
				}
				//thread = new std::thread(&basicfunction::execute, function, argumentspointer, sharederrorcodepointer, forced, this);
				thread = std::thread(
					[this, argumentspointer, forced] {
						function->execute(argumentspointer, sharederrorcodepointer, forced, this);
						alive = false;
					}
				);
			}
			else if (errorcodepointer) {
				*errorcodepointer = 7658;	//change error code (to do): cant execute nullptr of function
			}
		}
		void stream::killstream(stream* caller) {
			if (alive) {
				if (caller) {
					if (this->caller) {
						if (caller->id == this->caller->id) {
							goto killstream;
						}
					}
					if (caller->rights->getkillrights()) {
						goto killstream;
					}
					if (this->id = caller->id) {
						goto killstream;
					}
				}
				return;
				killstream:
				std::cout << "kill" << std::endl;
				for (stream* s : childstreams) {
					s->killstream(this);
				}
				*sharederrorcodepointer = 0xFFFFFFFFFFFFFFFF;	//change, maybe temprorary value
				alive.wait(true);
				//unregister every used iteretor (to do)
				for (void* i : iterators) {
					((object::iterator*)i)->unregisterobject(this);
				}
				iterators.clear();
			}
		}
		void stream::joinstream(stream* caller) {
			if (caller->id == this->id) {
				return;
			}
			if (alive) {
				if (thread.joinable() && caller) {
					if (this->caller) {
						if (caller->id == this->caller->id) {
							return thread.join();
						}
					}
					if (caller->rights->getjoinrights()) {
						return thread.join();
					}
				}
			}
		}

		bool stream::isalive() {
			return alive;
		}
		bool stream::iswaiting() {
			if (alive) {
				//get semaphore value (to do)
			}
			return false;
		}
		uint64_t stream::getfunctionid() {
			if (function) {
				return function->getid();
			}
			return NULL;
		}
	}
}