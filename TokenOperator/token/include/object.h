#pragma once
#include "utils/include/dynamic_array.h"
#include "utils/include/pointer.h"
#include "type.h"
#include "container.h"
namespace dte_token {
	using dynamic_path = dte_utils::dynamic_array<dte_utils::dynamic_wstring>;
	struct object {
		dte_utils::dynamic_wstring	name;
		dte_utils::weak_ref<type>	t;		//type handler
		container					c;		//data container
		dte_utils::any_ref<void*>	data;
		dte_utils::dynamic_array<dte_utils::unknown_ref<object, false>>	childs;
		dte_utils::unknown_ref<object, false>* get_object(const dte_utils::dynamic_wstring& obj_name);
		dte_utils::unknown_ref<object, false>* get_object(dte_utils::dynamic_wstring&& obj_name);
		dte_utils::unknown_ref<object, false>* get_object(const dynamic_path& obj_path, size_t shift = 0);
		dte_utils::unknown_ref<object, false>* get_object(dynamic_path&& obj_path, size_t shift = 0);
	};
}