#include "../include/scope_path.h"
using namespace tokenoperator::dte_token::data;
scope_path::scope_path(size_t num_of_IDs, uint64_t* paths, uint64_t ID) : value<uint64_t*>(ID), size(num_of_IDs) {
	v = new uint64_t[size];
	size_t i = size;
	while (i) {
		v[i] = paths[--i];
	}
}
scope_path::scope_path(const scope_path& path) : value<uint64_t*>(path.ID), size(path.size) {
	v = new uint64_t[size];
	size_t i = size;
	while (i) {
		v[i] = path.v[--i];
	}
}
scope_path::scope_path(const scope_path& path1, const scope_path& path2, uint64_t ID) : value<uint64_t*>(ID), size(path1.size + path2.size) {
	v = new uint64_t[size];
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
	uint64_t* buffer = new uint64_t[size];
	size_t i = new_size, ii = from_index;
	while (i) {
		buffer[--i] = v[--ii];
	}
	delete[] v;
	size = new_size;
	v = buffer;
}