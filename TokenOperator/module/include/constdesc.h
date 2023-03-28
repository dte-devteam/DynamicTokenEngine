#pragma once
#include <vcruntime_string.h>	//for memcpy
#include "valuedesc.h"
namespace module {
	struct constdesc : valuedesc {
		using valuedesc::valuedesc;
		void* getpointer(void* getter = nullptr);
	};
}