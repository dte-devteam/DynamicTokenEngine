#include "../include/data_desc.h"
namespace data_desc {
	bool operator ==(typedesc& desc, uint32_t& supertype) {
		return desc.supertype == supertype;
	}
	bool operator ==(typedesc& desc, uint64_t& type) {
		return desc.supertype == type >> 32;
	}
	typedesc::typedesc(uint32_t supertype, size_t size, deletable_obj::DEL_F deleter) : supertype(supertype), size(size), deleter(deleter) {}
	uint32_t typedesc::getsupertype() const {
		return supertype;
	}
	uint64_t typedesc::gettype(uint32_t flags) const {
		uint64_t type = supertype;
		return (type << 32) | flags;
	}
	size_t typedesc::getsize() const {
		return size;
	}
	void typedesc::delete_obj(void* pointer) const {
		if (deleter) {
			deleter(pointer);
		}
	}
	valuedesc::valuedesc(typedesc type, void* pointer) : type(type), p(pointer){}
	typedesc valuedesc::gettypedesc() {
		return type;
	}
	void* vardesc::getpointer(void* getter) {
		return p;
	}
	void* constdesc::getpointer(void* getter) {
		return p && getter ? memcpy(getter, p, type.getsize()) : nullptr;
	}
}