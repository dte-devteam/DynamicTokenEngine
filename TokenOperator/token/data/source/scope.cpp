#include "../include/scope.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
scope::scope(size_t size, size_t prefered_size, uint64_t ID) : value<std::pair<smart_pointer<object>, bool>*>(ID), size(size), prefered_size(prefered_size) {
	v = new std::pair<smart_pointer<object>, bool>[size];
}
scope::scope(const scope& sc) : value<std::pair<smart_pointer<object>, bool>*>(sc.ID), size(sc.size), prefered_size(sc.prefered_size) {
	v = new std::pair<smart_pointer<object>, bool>[size];
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
	std::pair<smart_pointer<object>, bool>* buffer = new std::pair<smart_pointer<object>, bool>[new_size];
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
bool scope::add_object(smart_pointer<object> obj, bool is_base_of_scope) {
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
		std::pair<smart_pointer<object>, bool>* buffer = new std::pair<smart_pointer<object>, bool>[++size];
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
					v[i].second = false;
				}
				v[i].first = nullptr;
				return true;
			}
		}
	}
	return false;
}
smart_pointer<object> scope::get_object_forward(scope_path sp, size_t shift) {
	std::pair<smart_pointer<object>, bool> sop_b_pair = (*this)[(*sp)[shift]];
	if (++shift < sp.get_size()) {
		if (!sop_b_pair.second) {	//for debub and stability, but should be upgraded
			return nullptr;
		}
		return sop_b_pair.first.get_pointer() ? ((scope*)sop_b_pair.first.get_pointer())->get_object_forward(sp, shift) : sop_b_pair.first;
	}
	return sop_b_pair.first;
}
//smart_pointer<object> scope::get_object_backward(scope_path sp, size_t shift)
std::pair<smart_pointer<object>, bool> scope::operator[](uint64_t ID) {
	size_t i = size;
	while (i) {
		if (v[--i].first) {
			if (v[i].first->getID() == ID) {
				return v[i];
			}
		}
	}
	return { nullptr, false };
}
scope& scope::operator=(const scope& s�) {
	if (this == &s�) {
		return *this;
	}
	size_t i = size;
	while (i) {
		v[i] = s�.v[--i];
	}
	return *this;
}
size_t scope::get_size() {
	return size;
}
size_t scope::get_prefered_size() {
	return prefered_size;
}