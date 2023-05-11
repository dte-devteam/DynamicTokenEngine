#include "../include/constvalue.h"
namespace data {
	void* constvalue::getpointer(void* getter) {
		return p && getter ? memcpy(getter, p, type->getsize()) : nullptr;
	}
}