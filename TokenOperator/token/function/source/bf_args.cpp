#include "../include/bf_args.h"
using namespace tokenoperator::dte_token;
using namespace tokenoperator::dte_token::function;
bf_args::bf_args(size_t size, object** source) : size(size), data(new object*[size]){
	if (source) {
		size_t i = size;
		while (i) {
			data[i] = source[--i];
		}
	}
}
bf_args::bf_args(const bf_args& bfa) : bf_args(bfa.size, bfa.data) {}
bf_args::~bf_args() {
	delete[] data;
}
object** bf_args::get_data() const {
	return data;
}
size_t bf_args::get_size() const {
	return size;
}