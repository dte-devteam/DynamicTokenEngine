#pragma once
#include "valuedesc.h"
namespace module {
	struct vardesc : valuedesc {
		using valuedesc::valuedesc;
		void* getpointer(void* getter = nullptr);
	};
}