#include "../include/absolutestreamrights.h"
namespace stream {
	absolutestreamrights::absolutestreamrights(bool killstreamrights, bool semaphorerights, bool joinrights, bool memoryrights) : kill(killstreamrights) {
		kill = true; //temp, for testing
	}
	bool absolutestreamrights::getkillrights() {
		return kill;
	}
}