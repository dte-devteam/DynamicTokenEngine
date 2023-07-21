#pragma once
#include "token/object.h"
namespace tokenoperator::dte_token::function {

	struct bf_args {
		public:
			bf_args(size_t size, object** source = nullptr);
			bf_args(const bf_args& bfa);
			~bf_args();
			object** get_data() const;
			size_t get_size() const;
		protected:
			object** data;
			size_t size;
	};
}