#include "../include/object.h"
using namespace dte_token;
using namespace dte_utils;
unknown_ref<object, false>* object::get_object(const dte_utils::dynamic_wstring& obj_name) {
	return childs.find(
		[&obj_name](unknown_ref<object, false>& r) {
			return r.get_strong_owners() ? r->name == obj_name : false;
		}
	);
}
unknown_ref<object, false>* object::get_object(dte_utils::dynamic_wstring&& obj_name) {
	return childs.find(
		[&obj_name](unknown_ref<object, false>& r) {
			return r.get_strong_owners() ? r->name == obj_name : false;
		}
	);
}
unknown_ref<object, false>* object::get_object(const dynamic_path& obj_path, size_t shift) {
	unknown_ref<object, false>* obj = get_object(obj_path[shift]);
	if (++shift < obj_path.get_used_size() && obj) {
		return (*obj)->get_object(obj_path, shift);
	}
	return obj;
}
unknown_ref<object, false>* object::get_object(dynamic_path&& obj_path, size_t shift) {
	unknown_ref<object, false>* obj = get_object(obj_path[shift]);
	if (++shift < obj_path.get_used_size() && obj) {
		return (*obj)->get_object(obj_path, shift);
	}
	return obj;
}