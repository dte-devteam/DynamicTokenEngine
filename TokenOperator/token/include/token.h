#pragma once
#include "utils/include/dynamic_memory/dynamic_string.h"
#include "utils/include/pointer/unknown_ref.h"
namespace dte_token {
	struct token {
		struct link {
			dte_utils::unknown_ref<token> pointer;
			dte_utils::dynamic_wstring pseudonym;
		};
		//protected:
			dte_utils::dynamic_array<link> links;
		public:
			~token() {
				std::cout << "~token" << std::endl;
			}
	};
}