#pragma once
#include "utils/include/dictionary.h"
#include "utils/include/pointer.h"
#include "token/include/function.h"
#include "token/include/object.h"
namespace dte_parser {
	/*
	token - is main pseudograph
	 - contains function (if defined and filled)
	 - contains data (if object and data is set)
	*/
	struct token {
		struct relation {
			dte_utils::dynamic_wstring text;
			//dte_utils::dictionary<dte_utils::dynamic_wstring, bool> flags;	//possible analysis
		};
		struct metainfo {
			dte_token::function func;
			//data (object)
		};
		struct link {
			dte_utils::unknown_ref<token, false> pointer;
			relation token_relation;
			dte_utils::dynamic_wstring pseudonym;
			dte_utils::dynamic_wstring& getcallname();
			const dte_utils::dynamic_wstring& getcallname() const;
		};
		public:
			//~token();
		protected:
			dte_utils::dynamic_wstring name;
			metainfo meta;
			dte_utils::dynamic_array<link> links;
	};
}