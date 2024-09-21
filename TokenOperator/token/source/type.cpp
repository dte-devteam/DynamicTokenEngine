#include "../include/type.h"
using namespace dte_utils;
namespace dte_token {
	type& type::operator=(const type& other_type) noexcept {
		if (this == &other_type) {
			return *this;
		}
		name = (dynamic_array<wchar_t>)other_type.name;
		return *this;
	}
	type& type::operator=(type&& other_type) noexcept {
		if (this == &other_type) {
			return *this;
		}
		name = std::move(other_type.name);
		return *this;
	}
	bool type::operator==(const type& other_type) const noexcept {
		return name == other_type.name;
	}
}