#include "../include/complex_type.h"
using namespace tokenoperator::dte_token::data;
complex_type::complex_type(size_t fields_to_add, object* types_to_add, create_value_function* constructors_of_types, uint64_t ID) : value<std::pair<type<void>, create_value_function>*>(ID), number_of_fields(fields_to_add) {
	v = new std::pair<type<void>, create_value_function>[fields_to_add];
	size_t i = 0;
	while (i < fields_to_add) {
		v[i++] = std::make_pair(((type<void>*)types_to_add)[i], constructors_of_types[i]);
	}
}
complex_type::complex_type(const complex_type& ct) : value<std::pair<type<void>, create_value_function>*>(ct.ID), number_of_fields(ct.number_of_fields) {
	v = new std::pair<type<void>, create_value_function>[number_of_fields];
	size_t i = 0;
	while (i < number_of_fields) {
		v[i++] = ct.v[i];
	}
}
complex_type::complex_type(const complex_type& ct1, const complex_type& ct2, uint64_t ID) : value<std::pair<type<void>, create_value_function>*>(ID), number_of_fields(ct1.number_of_fields + ct2.number_of_fields) {
	v = new std::pair<type<void>, create_value_function>[number_of_fields];
	size_t i = 0, ii = 0;
	while (ii < ct1.number_of_fields) {
		v[i++] = ct1.v[ii++];
	}
	ii = 0;
	while (ii < ct2.number_of_fields) {
		v[i++] = ct1.v[ii++];
	}
}
complex_type::~complex_type() {
	delete[] v;
}
complex_type& complex_type::operator=(const complex_type& ct) {
	if (this == &ct) {
		return *this;
	}
	number_of_fields = ct.number_of_fields;
	size_t i = 0;
	while (i < number_of_fields) {
		v[i++] = ct.v[i];
	}
}
size_t complex_type::get_number_of_fields() {
	return number_of_fields;
}