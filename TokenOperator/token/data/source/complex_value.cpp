#include "../include/complex_value.h"
using namespace tokenoperator::dte_token::data;
complex_value::complex_value(complex_type heap, uint64_t ID) : value<object*>(ID), heap(heap) {
	v = (object*)malloc(sizeof(object*) * heap.get_number_of_fields());
	size_t i = 0;
	size_t size = heap.get_number_of_fields();
	//to do (create values by create function)
	while (i < size) {
		//v[i++] = heap.create_value
	}
}
complex_value::~complex_value() {
	object* i = v;
	object* end = i + heap.get_number_of_fields();
	while (i < end) {
		i++->~object();
	}
	free(v);
}