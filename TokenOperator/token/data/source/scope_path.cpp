#include "../include/scope_path.h"
using namespace tokenoperator::dte_token::data;
scope_path::scope_path(size_t num_of_paths, std::pair<uint64_t, bool>* paths, uint64_t ID) : value<std::pair<uint64_t, bool>*>(ID), size(num_of_paths) {
	v = new std::pair<uint64_t, bool>[size];
	size_t i = size;
	while (i) {
		v[i] = paths[--i];
	}
}
scope_path::scope_path(const scope_path& path) : value<std::pair<uint64_t, bool>*>(path.ID), size(path.size) {
	v = new std::pair<uint64_t, bool>[size];
	size_t i = size;
	while (i) {
		v[i] = path.v[--i];
	}
}
scope_path::scope_path(const scope_path& path1, const scope_path& path2, uint64_t ID) : value<std::pair<uint64_t, bool>*>(ID), size(path1.size + path2.size) {
	v = new std::pair<uint64_t, bool>[size];
	size_t i = size, ii = path2.size;
	while (ii) {
		v[--i] = path2.v[--ii];
	}
	ii = path1.size;
	while (ii) {
		v[--i] = path1.v[--ii];
	}
}
scope_path::~scope_path() {
	delete[] v;
}
scope_path& scope_path::operator=(const scope_path& sp) {
	if (this == &sp) {
		return *this;
	}
	ID = sp.ID;
	if (size != sp.size) {
		delete[] v;
		size = sp.size;
		v = new std::pair<uint64_t, bool>[size];
	}
	size_t i = size;
	while (i) {
		v[i] = sp.v[--i];
	}
	return *this;
}
size_t scope_path::get_size() {
	return size;
}
void scope_path::clip(size_t from_index, size_t to_index) {
	if (from_index > size) {
		from_index = size;
	}
	if (to_index > size) {
		to_index = size;
	}
	size_t new_size = to_index - from_index;
	std::pair<uint64_t, bool>* buffer = new std::pair<uint64_t, bool>[new_size];
	size_t i = to_index, ii = new_size;
	while (ii) {
		buffer[--i] = v[--ii];
	}
	delete[] v;
	size = new_size;
	v = buffer;
}