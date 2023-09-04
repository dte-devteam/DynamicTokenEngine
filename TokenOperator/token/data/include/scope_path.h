#pragma once
#include "value.h"
#define EMPTY_SCOPE_PATH(ID) scope_path(0, nullptr, ID)
namespace tokenoperator::dte_token::data {
	struct scope_path : value<std::pair<uint64_t, bool>*> {
		public:
			scope_path(size_t num_of_paths, std::pair<uint64_t, bool>* paths, uint64_t ID = 0);
			scope_path(const scope_path& path);
			scope_path(const scope_path& path1, const scope_path& path2, uint64_t ID = 0);
			~scope_path();
			scope_path& operator=(const scope_path& sp);
			bool operator==(const scope_path& sp);
			size_t get_size();
			void clip(size_t from_index, size_t to_index);
		protected:
			size_t size;
	};
	/*
	* path format:
	* root/lvl1/lvl2 -> lvl2 <- root\\lvl1\\lvl2
	* root/lvl1/lvl2/.lvl1 -> lvl1 <- root\\lvl1\\lvl2\\.lvl1
	* "." - means that path is backward, "\\"/"/" - separates token names
	* 
	* classic "." that means "this folder" has no scence - if we has this folder for getting other object, we already has "this folder"
	*/
	inline scope_path token_path(const wchar_t* wstr, size_t wstr_len, uint64_t ID = 0) {
		size_t num_of_paths = 1, i = wstr_len;
		while (i) {
			if (wstr[--i] == L'\\' || wstr[i] == L'/') {
				++num_of_paths;
			}
		}
		std::pair<uint64_t, bool>* paths = new std::pair<uint64_t, bool>[num_of_paths];
		i = num_of_paths;
		wchar_t* end = (wchar_t*)wstr + wstr_len, prev = L'\0';
		wchar_t* witer = end;
		while (witer > wstr) {
			--witer;
			if (*witer == L'\\' || *witer == L'/') {
				if (prev == L'.') {
					paths[--i] = {
						token_name(witer + 2, end - (witer + 2)), true
					};
				}
				else {
					paths[--i] = {
						token_name(witer + 1, end - (witer + 1)), false
					};
				}
				end = witer;
			}
			prev = *witer;
		}
		if (prev == L'.') {
			paths[--i] = {
				token_name(witer + 1, end - (witer + 1)), true
			};
		}
		else {
			paths[--i] = {
				token_name(witer, end - witer), false
			};
		}
		scope_path path(num_of_paths, paths, ID);
		delete[] paths;
		return path;
	}
}