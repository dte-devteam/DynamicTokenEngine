#include "../include/complex_value.h"
using namespace tokenoperator::dte_token::data;
complex_value::complex_value(complex_type heap, uint64_t ID) : scope(heap.get_number_of_fields(), heap.get_number_of_fields(), ID), heap(heap) {
	size_t i = size;
	while (i) {
		v[i].first = ((*heap)[--i].first.first)(i);
		v[i].second = (*heap)[i].second;
	}
}
complex_value::complex_value(const complex_value& cv) : scope(cv), heap(cv.heap) {}
complex_value::complex_value(complex_value* cv, uint64_t ID) : scope(cv->size, cv->size, ID), heap(cv->heap) {
	size_t i = size;
	while (i) {
		v[i].first = ((*heap)[--i].first.second)(cv->v[i].first, i);
		v[i].second = cv->v[i].second;
	}
}
smart_object_pointer complex_value::deep_copy(uint64_t copy_ID, uint64_t pointer_ID) {
	if (heap.is_copyable()) {
		return smart_object_pointer(new complex_value(this, copy_ID), pointer_ID);
	}
	return smart_object_pointer(nullptr, pointer_ID);
}