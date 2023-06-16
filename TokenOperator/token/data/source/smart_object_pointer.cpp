#include "../include/smart_object_pointer.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
smart_object_pointer::smart_object_pointer(object* pointer, uint64_t ID) : value<object*>(ID), owner_num(new size_t[]{1}) {
	v = pointer;
}
smart_object_pointer::smart_object_pointer(const smart_object_pointer& sop) : value<object*>(ID), owner_num(sop.owner_num) {	
	v = sop.v;
	++*owner_num;
}
smart_object_pointer::~smart_object_pointer() {
	if (!--*owner_num) {
		delete v;
		delete[] owner_num;
	}
}
smart_object_pointer& smart_object_pointer::operator=(const smart_object_pointer& sop) {
	if (this == &sop) {
		return *this;
	}
	if (v != sop.v) {
		if (!--*owner_num) {
			delete v;
			delete[] owner_num;
		}
		v = sop.v;
		owner_num = sop.owner_num;
		++*owner_num;
	}
	return *this;
}
smart_object_pointer& smart_object_pointer::operator=(object* pointer) {
	if (v != pointer) {
		if (!--*owner_num) {
			delete v;
			delete[] owner_num;
		}
		v = pointer;
		owner_num = new size_t[]{1};
	}
	return *this;
}
explicit smart_object_pointer::operator object* () {
	return v;
}
object* smart_object_pointer::operator*() {
	return v;
}
object* smart_object_pointer::operator->() {
	return v;
}