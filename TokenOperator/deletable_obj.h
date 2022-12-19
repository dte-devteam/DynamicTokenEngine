#pragma once
namespace deletable_obj {
	template <typename T> void destructor(void* pointer) {
		delete (T*)pointer;
	}
}