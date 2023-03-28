#include "../include/absolutestreamrights.h"
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
}