#pragma once
#include "utils/include/dictionary.h"
#include "utils/include/pointer.h"
#include "token/include/function.h"
#include "token/include/type.h"
namespace dte_utils {
	using dynamic_path = dynamic_array<dynamic_wstring>;
}
namespace dte_token {
	/*
	token - is main pseudograph
	 - contains function (if defined and set)
	 - contains data (if defined is set)
	*/
	struct token {
		struct relation {
			dte_utils::dynamic_wstring text;
			//dte_utils::dictionary<dte_utils::dynamic_wstring, bool> flags;	//possible analysis
		};
		struct metainfo {
			dte_utils::weak_ref<function>	f;		//function handler
			dte_utils::weak_ref<type>		t;		//type handler
			dte_utils::any_ref<void>		d;		//data handler
		};
		struct link {
			dte_utils::unknown_ref<token, false> pointer;
			relation token_relation;
			dte_utils::dynamic_wstring pseudonym;
			dte_utils::dynamic_wstring& getcallname();
			const dte_utils::dynamic_wstring& getcallname() const;
		};
		public:
			link* get_token(const dte_utils::dynamic_wstring& token_name);
			link* get_token(dte_utils::dynamic_wstring&& token_name);
			link* get_token(const dte_utils::dynamic_path& token_path, size_t shift = 0);
			link* get_token(dte_utils::dynamic_path&& token_path, size_t shift = 0);
		protected:
			dte_utils::dynamic_wstring name;
			metainfo meta;
			dte_utils::dynamic_array<link> links;
	};
}