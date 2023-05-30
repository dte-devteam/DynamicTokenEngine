#include "../include/complex_value.h"
using namespace tokenoperator::dte_token::data;
complex_value::complex_value(complex_type heap, uint64_t ID) : value<object**>(ID), heap(heap) {
	size_t i = 0;
	size_t size = heap.get_number_of_fields();
	v = new object*[size];
	while (i < size) {
		v[i++] = ((*heap)[i].second)(i);
	}
}
complex_value::~complex_value() {
	size_t i = 0;
	size_t size = heap.get_number_of_fields();
	while (i < size) {
		delete v[i++];
	}
	delete[] v;
}