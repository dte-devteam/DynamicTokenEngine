#include "../include/type.h"
using namespace dte_token;
using namespace dte_utils;
bool type::is_same_as(const type& other_type) const noexcept {
	return name == other_type.name;
}
bool type::is_parent_of(const type& other_type) const noexcept {
	return other_type.parents.find(
		[this](const weak_ref<type>& iter) noexcept {
			return name == iter->name;
		}
	);
}
bool type::is_child_of(const type& other_type) const noexcept {
	return parents.find(
		[this](const weak_ref<type>& iter) noexcept {
			return name == iter->name;
		}
	);
}
type& type::operator=(const type& other_type) noexcept {
	if (this == &other_type) {
		return *this;
	}
	name = other_type.name;
	parents = other_type.parents;
	return *this;
}
type& type::operator=(type&& other_type) noexcept {
	if (this == &other_type) {
		return *this;
	}
	name = std::move(other_type.name);
	parents = std::move(other_type.parents);
	return *this;
}