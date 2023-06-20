#include "../include/complex_type.h"
using namespace tokenoperator::dte_token::data;
complex_type::complex_type(size_t fields_to_add, object* types_to_add, value_functions* constructors_and_copyres_of_values, uint64_t ID) : value<std::pair<type<void>, std::pair<create_value_function, copy_value_function>>*>(ID), number_of_fields(fields_to_add), copyable(true){
	v = new std::pair<type<void>, std::pair<create_value_function, copy_value_function>>[fields_to_add];
	size_t i = number_of_fields;
	while (i) {
		copyable = constructors_and_copyres_of_values[--i].second && copyable;
		v[i] = std::make_pair(((type<void>*)types_to_add)[i], constructors_and_copyres_of_values[i]);
	}
}
complex_type::complex_type(const complex_type& ct) : value<std::pair<type<void>, value_functions>*>(ct.ID), number_of_fields(ct.number_of_fields), copyable(ct.copyable) {
	v = new std::pair<type<void>, std::pair<create_value_function, copy_value_function>>[number_of_fields];
	size_t i = number_of_fields;
	while (i) {
		v[i] = ct.v[--i];
	}
}
complex_type::complex_type(const complex_type& ct1, const complex_type& ct2, uint64_t ID) : value<std::pair<type<void>, value_functions>*>(ID), number_of_fields(ct1.number_of_fields + ct2.number_of_fields), copyable(ct1.copyable && ct2.copyable) {
	v = new std::pair<type<void>, std::pair<create_value_function, copy_value_function>>[number_of_fields];
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
	ID = ct.ID;
	if (number_of_fields != ct.number_of_fields){
		delete[] v;
		number_of_fields = ct.number_of_fields;
		v = new std::pair<type<void>, value_functions>[number_of_fields];
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