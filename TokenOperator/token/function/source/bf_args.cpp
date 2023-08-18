#include "../include/bf_args.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::function;
bf_args::bf_args(size_t size, object** source) : size(size), data(size ? new object*[size]{0} : nullptr) {
	if (source) {
		size_t i = size;
		while (i) {
			data[i] = source[--i];
		}
	}
}
bf_args::bf_args(const bf_args& bfa) : bf_args(bfa.size, bfa.data) {}
bf_args::bf_args(const bf_args& input_bfa, const bf_args& default_bfa) : bf_args(std::max(input_bfa.get_size(), default_bfa.get_size())) {
	object** input_source = input_bfa.get_data();
	object** default_source = default_bfa.get_data();
	size_t i = default_bfa.get_size();
	while (i) {
		data[i] = default_source[--i];
	}
	i = input_bfa.get_size();
	while (i) {
		if (input_source[--i]) {
			data[i] = input_source[i];
		}
	}
}
bf_args::~bf_args() {
	delete[] data;
}
bf_args& bf_args::operator=(const bf_args& bfa) {
	if (&bfa == this) {
		return *this;
	}
	if (size != bfa.size) {
		size = bfa.size;
		delete[] data;
		data = size ? new object*[size]{0} : nullptr;
	}
	size_t i = size;
	while (i) {
		data[i] = bfa.data[--i];
	}
	return *this;
}
object** bf_args::get_data() const {
	return data;
}
size_t bf_args::get_size() const {
	return size;
}