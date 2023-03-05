#include "../include/type_desc.h"
namespace type_desc {
	typedesc::typedesc(uint32_t type, size_t size) : type(type), size(size){}
	uint32_t typedesc::gettype() {
		return type;
	}
	size_t typedesc::getsize() {
		return size;
	}
}