#pragma once
#include "utils/include/dynamic_array.h"
#include "utils/include/pointer.h"
#include "relation.h"
namespace dte_parser {
	struct token {
		//to do string token_name
		relation token_relation;
		bool arrayforced;
		dte_utils::dynamic_array<dte_utils::strong_ref<token, false>> token_childs;
	};
}