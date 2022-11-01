#include "../include/thread.h"
namespace memory {
	namespace stream {
		stream::stream(basicfunction* function, uint64_t id, stream* caller) : id(id), caller(caller) {}
		stream::~stream(){}
	}
}