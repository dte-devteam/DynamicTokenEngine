#include "../include/complex_value.h"
using namespace tokenoperator::dte_token::data;
complex_value::complex_value(complex_type heap, uint64_t ID) : scope(heap.get_number_of_fields(), heap.get_number_of_fields(), ID), heap(heap) {
	size_t i = 0;
	while (i < size) {
		v[i++] = ((*heap)[i].second.first)(i);
	}
}
complex_value::complex_value(const complex_value& cv) : scope(cv.size, cv.size, cv.ID), heap(cv.heap) {
	size_t i = 0;
	v = new object*[size];
	while (i < size) {
		if ((*heap)[i].second.second) {	//if value is copyable - we copy value
			v[i++] = ((*heap)[i].second.second)(cv.v[i], cv.v[i]->getID());
		}
	}
}
complex_value::~complex_value() {
	size_t i = 0;
	while (i < size) {
		delete v[i++];
	}
}