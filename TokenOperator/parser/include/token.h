#pragma once
#include "utils/include/dynamic_array.h"
#include "relation.h"
namespace dte_parser {
	struct token {
		//to do string token_name
		relation token_relation;
		bool arrayforced;
		dte_utils::dynamic_array<token> token_childs;
	};
}