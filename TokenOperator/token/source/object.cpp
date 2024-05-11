#include "../include/object.h"
using namespace dte_token;
using namespace dte_utils;
dynamic_wstring& object::link::getcallname() {
	return pseudonym.get_used_size() ? pseudonym : pointer->name;
}
const dynamic_wstring& object::link::getcallname() const {
	return pseudonym.get_used_size() ? pseudonym : pointer->name;
}
const object::link* object::get_object(const dynamic_wstring& obj_name) const {
	return childs.find(
		[&obj_name](const object::link& iter) {
			return iter.getcallname() == obj_name;
		}
	);
}
const object::link* object::get_object(dynamic_wstring&& obj_name) const {
	return childs.find(
		[&obj_name](const object::link& iter) {
			return iter.getcallname() == obj_name;
		}
	);
}
const object::link* object::get_object(const dynamic_path& obj_path, size_t shift) const {
	const link* obj = get_object(obj_path[shift]);
	if (++shift < obj_path.get_used_size() && obj) {
		return obj->pointer->get_object(obj_path, shift);
	}
	return obj;
}
const object::link* object::get_object(dynamic_path&& obj_path, size_t shift) const {
	const link* obj = get_object(obj_path[shift]);
	if (++shift < obj_path.get_used_size() && obj) {
		return obj->pointer->get_object(obj_path, shift);
	}
	return obj;
}