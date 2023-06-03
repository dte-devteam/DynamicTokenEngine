#include "../include/complex_value.h"
using namespace tokenoperator::dte_token::data;
complex_value::complex_value(complex_type heap, uint64_t ID) : value<object**>(ID), heap(heap) {
	size_t i = 0, size = heap.get_number_of_fields();
	v = new object*[size];
	while (i < size) {
		v[i++] = ((*heap)[i].second.first)(i);
	}
}
complex_value::complex_value(const complex_value& cv) : value<object**>(cv.ID), heap(cv.heap) {
	size_t i = 0, size = heap.get_number_of_fields();
	v = new object * [size];
	while (i < size) {
		v[i++] = ((*heap)[i].second.second)(cv.v[i], cv.v[i]->getID());
	}
}
complex_value::~complex_value() {
	size_t i = 0, size = heap.get_number_of_fields();
	while (i < size) {
		delete v[i++];
	}
	delete[] v;
}