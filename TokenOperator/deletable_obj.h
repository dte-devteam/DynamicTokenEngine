#pragma once
namespace deletable_obj {
	typedef void (*DEL_F)(void*);
	template <typename T> void destructor(void* pointer) {
		delete (T*)pointer;
	}
}