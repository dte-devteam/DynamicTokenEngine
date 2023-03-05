#include "../include/values.h"
namespace data {
	staticdata::staticdata(size_t size, uint64_t name, void* pointer) : size(size), name(name) {
		p = pointer ? pointer : calloc(1, size);
	}
	staticdata::~staticdata() {
		free(p);
	}
	size_t staticdata::getsize() {
		return size;
	}
	uint64_t staticdata::getname() {
		return name;
	}
	void* staticdata::getpointer() {
		return p;
	}
}