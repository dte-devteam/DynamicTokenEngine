#include "../include/complex_type.h"
using namespace tokenoperator::dte_token::data;
complex_type::complex_type(size_t fields_to_add, value_functions* constructors_and_copyres_of_values, bool* is_base_of_scope, uint64_t ID) : value<std::pair<value_functions, bool>*>(ID), number_of_fields(fields_to_add), copyable(true){
	v = new std::pair<value_functions, bool>[number_of_fields];
	size_t i = number_of_fields;
	while (i) {
		v[i].first = constructors_and_copyres_of_values[--i];
		v[i].second = is_base_of_scope[i];
	}
}
complex_type::complex_type(const complex_type& ct) : value<std::pair<value_functions, bool>*>(ct.ID), number_of_fields(ct.number_of_fields), copyable(ct.copyable) {
	v = new std::pair<value_functions, bool>[number_of_fields];
	size_t i = number_of_fields;
	while (i) {
		v[i] = ct.v[--i];
	}
}
complex_type::complex_type(const complex_type& ct1, const complex_type& ct2, uint64_t ID) : value<std::pair<value_functions, bool>*>(ID), number_of_fields(ct1.number_of_fields + ct2.number_of_fields), copyable(ct1.copyable && ct2.copyable) {
	v = new std::pair<value_functions, bool>[number_of_fields];
	size_t i = number_of_fields, ii = ct2.number_of_fields;
	while (ii) {
		v[--i] = ct1.v[--ii];
	}
	ii = ct1.number_of_fields;
	while (ii) {
		v[--i] = ct1.v[--ii];
	}
}
complex_type::~complex_type() {
	delete[] v;
}
complex_type& complex_type::operator=(const complex_type& ct) {
	if (this == &ct) {
		return *this;
	}
	if (number_of_fields != ct.number_of_fields){
		delete[] v;
		number_of_fields = ct.number_of_fields;
		v = new std::pair<value_functions, bool>[number_of_fields];
	}
	copyable = ct.copyable;
	size_t i = number_of_fields;
	while (i) {
		v[i] = ct.v[--i];
	}
	return *this;
}
size_t complex_type::get_number_of_fields() {
	return number_of_fields;
}
bool complex_type::is_copyable() {
	return copyable;
}