#include "../include/scope.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
scope::scope(size_t size, size_t prefered_size, uint64_t ID) : value<object**>(ID), size(size), prefered_size(prefered_size) {
	v = new object*[size]{0};
}
scope::scope(const scope& sc) : value<object**>(sc.ID), size(sc.size), prefered_size(sc.prefered_size) {
	v = new object*[size]{0};
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
	object** buffer = new object*[new_size];
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
	object** temp = v;
	v = buffer;
	delete[] temp;
}
bool scope::add_object(object* obj) {
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
		object** buffer = new object*[++size];
		i = size - 1;
		while (i) {
			buffer[i] = v[--i];
		}
		buffer[size] = obj;
		object** temp = v;
		v = buffer;
		delete[] temp;
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
object* scope::get_object(scope_path s, size_t shift) {
	object* o = (*this)[s.IDs[shift++]];
	if (shift < s.size) {
		return o ? ((scope*)o)->get_object(s, shift) : o;
	}
	return o;
}
object* scope::operator[](uint64_t ID) {
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
size_t scope::get_size() {
	return size;
}
size_t scope::get_prefered_size() {
	return prefered_size;
}