#pragma once
#include "utils/include/dictionary.h"
#include "utils/include/pointer.h"
namespace dte_parser {
	typedef bool (*unknown_function)();
	struct token {
		struct relation {
			dte_utils::dynamic_wstring text;
			dte_utils::dictionary<dte_utils::dynamic_wstring, bool> flags;
		};
		struct metainfo {
			unknown_function this_execution;
			unknown_function next_execution;
			unknown_function jump_execution;
			template<typename ...Args>
			unknown_function execute(Args... args) {
				if (this_execution == nullptr) {
					//to do throw
				}
				return ((bool (*)(Args))this_execution)(args...) ? jump_execution : next_execution;
			}
		};
		struct link {
			dte_utils::unknown_ref<token, false> pointer;
			relation token_relation;
		};
		public:
			//~token();
		protected:
			dte_utils::dynamic_wstring name;
			metainfo meta;
			dte_utils::dynamic_array<link> links;
	};
}