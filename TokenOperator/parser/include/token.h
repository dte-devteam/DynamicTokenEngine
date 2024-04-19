#pragma once
#include "utils/include/dynamic_array.h"
#include "utils/include/pointer.h"
namespace dte_parser {
	struct token {
		//relation can be inherited and upgraded
		struct relation {
			size_t version;
		};
		//metainfo can be inherited and upgraded
		struct metainfo {
			size_t version;
		};
		struct link {
			dte_utils::unknown_ref<token, false> pointer;
			relation* token_relation;
			~link();
		};
		public:
			~token();
		protected:
			dte_utils::dynamic_array<wchar_t> text;
			//think about fast finding (something like id by hash...)
			metainfo* meta;
			dte_utils::dynamic_array<link> links;
	};
}