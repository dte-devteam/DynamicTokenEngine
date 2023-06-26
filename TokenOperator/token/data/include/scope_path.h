#pragma once
#include "value.h"
//to do (data for fast access in scope)
namespace tokenoperator::dte_token::data {
	struct scope_path : value<std::pair<uint64_t, bool>*> {
		public:	//protected:
			scope_path(size_t num_of_paths, std::pair<uint64_t, bool>* paths, uint64_t ID = 0);
			scope_path(const scope_path& path);
			scope_path(const scope_path& path1, const scope_path& path2, uint64_t ID = 0);
			~scope_path();
			scope_path& operator=(const scope_path& sp);
			size_t get_size();
			void clip(size_t from_index, size_t to_index);
		protected:
			size_t size;
	};
}