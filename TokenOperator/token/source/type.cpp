#include "../include/type.h"
using namespace dte_utils;
namespace dte_token {
	bool type::is_same_as(const type& other_type) const noexcept {
		return name == other_type.name;
	}
	type& type::operator=(const type& other_type) noexcept {
		if (this == &other_type) {
			return *this;
		}
		name = other_type.name;
		return *this;
	}
	type& type::operator=(type&& other_type) noexcept {
		if (this == &other_type) {
			return *this;
		}
		name = std::move(other_type.name);
		return *this;
	}
}