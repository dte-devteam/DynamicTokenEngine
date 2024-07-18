#pragma once
#include "utils/include/pointer.h"
#include "type.h"
namespace dte_token {
	struct data {
		dte_utils::weak_ref<type>	t;
		dte_utils::any_ref<void>	d;
	};
}