#include "../include/scope.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
scope::scope(size_t size, size_t prefered_size, uint64_t ID) : value<std::pair<smart_object_pointer, bool>*>(ID), size(size), prefered_size(prefered_size) {
	v = new std::pair<smart_object_pointer, bool>[size];
}
scope::scope(const scope& sc) : value<std::pair<smart_object_pointer, bool>*>(sc.ID), size(sc.size), prefered_size(sc.prefered_size) {
	v = new std::pair<smart_object_pointer, bool>[size];
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
		if (!v[--i].first) {
			min_size++;
		}
	}
	size_t new_size = min_size > prefered_size ? min_size : prefered_size;
	std::pair<smart_object_pointer, bool>* buffer = new std::pair<smart_object_pointer, bool>[new_size];
	i = size;
	ii = new_size;
	while (i) {
		if (!v[--i].first) {
			buffer[--ii] = v[i];
		}
	}
	delete[] v;
	v = buffer;
}
bool scope::add_object(smart_object_pointer obj, bool is_base_of_scope) {
	if (obj) {
		size_t i = size;
		while (i) {
			if (!v[--i].first) {
				v[i].first = obj;
				v[i].second = is_base_of_scope;
				if (is_base_of_scope) {
					//to add this to child
				}
				return true;
			}
			else if (v[i].first->getID() == obj->getID()) {
				return false;
			}
		}
		std::pair<smart_object_pointer, bool>* buffer = new std::pair<smart_object_pointer, bool>[++size];
		i = size - 1;
		while (i) {
			buffer[i] = v[--i];
		}
		buffer[size].first = obj;
		buffer[size].second = is_base_of_scope;
		delete[] v;
		v = buffer;
	}
	return true;
}
bool scope::remove_object(uint64_t ID) {
	size_t i = size;
	while (i) {
		if (v[--i].first) {
			if (v[i].first->getID() == ID) {
				if (v[i].second) {
					//to do (revome from child pointer to this)
				}
				v[i].first = nullptr;
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
		if (v[--i].first) {
			if (v[i].first->getID() == ID) {
				return v[i].first;
			}
		}
	}
	return nullptr;
}
scope& scope::operator=(const scope& sñ) {
	if (this == &sñ) {
		return *this;
	}
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