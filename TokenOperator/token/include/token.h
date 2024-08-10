#pragma once
#include "utils/include/dynamic_array.h"
#include "data.h"
namespace dte_utils {
	typedef dynamic_array<dynamic_wstring> dynamic_path;
}
namespace dte_token {
	/*
	token - is main pseudograph
	 - contains function (if defined and set)
	 - contains data (if defined is set)
	*/
	struct token : data {
		struct link {
			dte_utils::unknown_ref<token, false> pointer;
			dte_utils::dynamic_wstring pseudonym;
			dte_utils::dynamic_wstring& getcallname();
			const dte_utils::dynamic_wstring& getcallname() const;
		};
		public:
			link* get_token(const dte_utils::dynamic_wstring& token_name) const;
			link* get_token(dte_utils::dynamic_wstring&& token_name) const;
			link* get_token(const dte_utils::dynamic_path& token_path, size_t shift = 0) const;
			link* get_token(dte_utils::dynamic_path&& token_path, size_t shift = 0) const;
			void copy_links(const token& source);
			//protected:
			dte_utils::dynamic_wstring name;
			dte_utils::dynamic_array<link> links;
	};
}