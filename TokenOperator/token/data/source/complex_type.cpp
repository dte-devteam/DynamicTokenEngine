#include "../include/complex_type.h"
using namespace tokenoperator::dte_token::data;
complex_type::complex_type(uint64_t ID) : value<std::pair<type<void>, create_value_function>*>(ID), number_of_fields(0) {
	v = nullptr;
}
complex_type::~complex_type() {
	delete[] v;
}
size_t complex_type::get_number_of_fields() const {
	return number_of_fields;
}
complex_type complex_type::generate_child(size_t fields_to_add, object* types_to_add, create_value_function* constructors_of_types, uint64_t ID) const {
	complex_type ct = complex_type(ID);
	ct.number_of_fields = number_of_fields + fields_to_add;
	ct.v = new std::pair<type<void>, create_value_function>[ct.number_of_fields];
	size_t i = 0, ii = 0;
	while (i < number_of_fields) {
		ct.v[i++] = v[i];
	}
	while (ii < fields_to_add) {
		ct.v[i].first = ((type<void>*)types_to_add)[ii];
		ct.v[i++].second = constructors_of_types[ii++];
	}
	return ct;
}