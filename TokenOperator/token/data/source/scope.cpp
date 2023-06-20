#include "../include/scope.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
scope::scope(size_t size, size_t prefered_size, uint64_t ID) : value<smart_object_pointer*>(ID), size(size), prefered_size(prefered_size) {
	v = new smart_object_pointer[size];
}
scope::scope(const scope& sc) : value<smart_object_pointer*>(sc.ID), size(sc.size), prefered_size(sc.prefered_size) {
	v = new smart_object_pointer[size];
	size_t i = size;
	while (i) {
		v[i] = sc.v[--i];
	}
}
scope::~scope() {
	delete[] v;
}
void scope::resize_to_prefered_size() {
	size_t min_size = 0, i = size, ii;
	while (i) {
		if (!v[--i]) {
			min_size++;
		}
	}
	size_t new_size = min_size > prefered_size ? min_size : prefered_size;
	smart_object_pointer* buffer = new smart_object_pointer[new_size];
	i = size;
	ii = new_size;
	while (i) {
		if (!v[--i]) {
			buffer[--ii] = v[i];
		}
	}
	while (ii) {
		buffer[--ii] = nullptr;
	}
	delete[] v;
	v = buffer;
}
bool scope::add_object(smart_object_pointer obj) {
	if (obj) {
		size_t i = size;
		while (i) {
			if (!v[--i]) {
				v[i] = obj;
				return true;
			}
			else if (v[i]->getID() == obj->getID()) {
				return false;
			}
		}
		smart_object_pointer* buffer = new smart_object_pointer[++size];
		i = size - 1;
		while (i) {
			buffer[i] = v[--i];
		}
		buffer[size] = obj;
		delete[] v;
		v = buffer;
	}
	return true;
}
bool scope::remove_object(uint64_t ID) {
	size_t i = size;
	while (i) {
		if (v[--i]) {
			if (v[i]->getID() == ID) {
				delete v[i];
				v[i] = nullptr;
				return true;
			}
		}
	}
	return false;
}
smart_object_pointer scope::get_object(scope_path sp, size_t shift) {
	smart_object_pointer o = (*this)[(*sp)[shift]];
	if (++shift < sp.get_size()) {
		return o ? ((scope*)*o)->get_object(sp, shift) : o;
	}
	return o;
}
smart_object_pointer scope::operator[](uint64_t ID) {
	size_t i = size;
	while (i) {
		if (v[--i]) {
			if (v[i]->getID() == ID) {
				return v[i];
			}
		}
	}
	return nullptr;
}
scope& scope::operator=(const scope& sñ) {
	if (this == &sñ) {
		return *this;
	}
	ID = sñ.ID;
	size_t i = size;
	while (i) {
		v[i] = sñ.v[--i];
	}
	return *this;
}
size_t scope::get_size() {
	return size;
}
size_t scope::get_prefered_size() {
	return prefered_size;
}