#include "../include/scope.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::data;
scope::scope(size_t size, size_t prefered_size, uint64_t ID) : value<std::pair<smart_pointer<object>, bool>*>(ID), size(size), prefered_size(prefered_size), root_num(0), roots(new scope*[0]) {
	v = new std::pair<smart_pointer<object>, bool>[size];
}
scope::scope(const scope& sc) : value<std::pair<smart_pointer<object>, bool>*>(sc.ID), size(sc.size), prefered_size(sc.prefered_size), root_num(0), roots(new scope* [0]) {
	v = new std::pair<smart_pointer<object>, bool>[size];
	size_t i = size;
	while (i) {
		v[i] = sc.v[--i];
	}
}
scope::~scope() {
	size_t i = size;
	while (i) {
		if (v[--i].second) {
			((scope*)v[i].first.get_pointer())->remove_root(this);
		}
	}
	delete[] v;
	delete[] roots;
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
		if (!v[--i].first.get_pointer()) {
			buffer[--ii] = v[i];
		}
	}
	delete[] v;
	v = buffer;
}
bool scope::add_object(smart_pointer<object> obj, bool is_base_of_scope) {
	if (obj.get_pointer()) {	//we can`t store nullptr, only a smart_pointer<object> that contains nullptr as value
		if (obj.get_pointer() == this) {	//scope can`t own itself
			return false;
		}
		size_t i = size, end;
		while (i) {
			if (!v[--i].first.get_pointer()) {
				v[i].first = obj;
				v[i].second = is_base_of_scope;
				if (is_base_of_scope) {
					((scope*)v[i].first.get_pointer())->add_root(this);
				}
				return true;
			}
			else if (v[i].first->getID() == obj->getID()) {
				return false;
			}
		}
		std::pair<smart_pointer<object>, bool>* buffer = new std::pair<smart_pointer<object>, bool>[++size];
		end = i = size - 1;
		while (i) {
			buffer[i] = v[--i];
		}
		buffer[end].first = obj;
		buffer[end].second = is_base_of_scope;
		if (is_base_of_scope) {
			((scope*)v[i].first.get_pointer())->add_root(this);
		}
		delete[] v;
		v = buffer;
	}
	return true;
}
bool scope::remove_object(uint64_t ID) {
	size_t i = size;
	while (i) {
		if (v[--i].first.get_pointer()) {
			if (v[i].first->getID() == ID) {
				if (v[i].second) {
					((scope*)v[i].first.get_pointer())->remove_root(this);
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
	if ((*sp)[shift].second) {
		return get_object_backward(sp, shift);
	}
	std::pair<smart_pointer<object>, bool> sop_b_pair = (*this)[(*sp)[shift].first];
	if (++shift < sp.get_size()) {
		if (sop_b_pair.second && sop_b_pair.first.get_pointer()) {
			return ((scope*)sop_b_pair.first.get_pointer())->get_object_forward(sp, shift);
		}
		return nullptr;
	}
	return sop_b_pair.first;
}
smart_pointer<object> scope::get_object_backward(scope_path sp, size_t shift) {
	if (!(*sp)[shift].second) {
		return get_object_forward(sp, shift);
	}
	//to do code
	return nullptr;
}
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
scope& scope::operator=(const scope& sc) {
	if (this == &sc) {
		return *this;
	}
	size_t i = size;
	while (i) {
		v[i] = sc.v[--i];
	}
	return *this;
}
size_t scope::get_size() {
	return size;
}
size_t scope::get_prefered_size() {
	return prefered_size;
}
void scope::add_root(scope* root) {
	size_t i = root_num, end = root_num;
	scope** buffer = new scope*[++root_num];
	while (i) {
		buffer[i] = roots[--i];
	}
	buffer[end] = root;
}
void scope::remove_root(scope* root) {
	size_t i = root_num, ii;
	while (i) {
		if (roots[--i] == root) {
			i = root_num;
			ii = --root_num;
			scope** buffer = new scope*[ii];
			//to do
		}
	}
}