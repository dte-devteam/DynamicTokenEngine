#pragma once
#include <vcruntime_string.h>	//for memcpy
#include "value.h"
namespace data {
	struct constvalue : value {
		using value::value;
		void* getpointer(void* getter = nullptr);
	};
}