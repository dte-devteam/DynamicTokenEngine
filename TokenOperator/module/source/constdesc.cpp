#include "../include/constdesc.h"
namespace module {
	void* constdesc::getpointer(void* getter) {
		return p && getter ? memcpy(getter, p, type->getsize()) : nullptr;
	}
}