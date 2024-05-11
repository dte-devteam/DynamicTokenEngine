#pragma once
#include "utils/include/dynamic_array.h"
#include "utils/include/pointer.h"
#include "type.h"
#include "container.h"
namespace dte_utils {
	using dynamic_path = dte_utils::dynamic_array<dte_utils::dynamic_wstring>;
}
namespace dte_token {
	/*
	object - is main data container
	*/
	struct object {
		struct link {
			dte_utils::unknown_ref<object, false> pointer;
			dte_utils::dynamic_wstring pseudonym;
			dte_utils::dynamic_wstring& getcallname();
			const dte_utils::dynamic_wstring& getcallname() const;
		};
		dte_utils::dynamic_wstring		name;
		dte_utils::weak_ref<type>		t;		//type handler
		container						c;		//data container
		dte_utils::any_ref<void*>		data;
		dte_utils::dynamic_array<link>	childs;
		const link* get_object(const dte_utils::dynamic_wstring& obj_name) const;
		const link* get_object(dte_utils::dynamic_wstring&& obj_name) const;
		const link* get_object(const dte_utils::dynamic_path& obj_path, size_t shift = 0) const;
		const link* get_object(dte_utils::dynamic_path&& obj_path, size_t shift = 0) const;
	};
}