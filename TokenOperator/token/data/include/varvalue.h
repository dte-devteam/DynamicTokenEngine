#pragma once
#include "value.h"
namespace data {
	struct varvalue : value {
		using value::value;
		void* getpointer(void* getter = nullptr);
	};
}