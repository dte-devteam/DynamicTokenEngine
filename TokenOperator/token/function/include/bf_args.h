#pragma once
#include "token/object.h"
#include <algorithm>
namespace tokenoperator::dte_token::function {
	/*
	* struct contains function args
	* args are pointers, because owner is a stream and user is basic_function
	* basic_function can`t be executed if stream does`t own it, so lifetime of basic_function is less than a stream
	* basic_function will use only alive objects, that provides stream
	*/
	struct bf_args {
		public:
			bf_args(size_t size, object** source = nullptr);
			bf_args(const bf_args& bfa);
			bf_args(const bf_args& input_bfa, const bf_args& default_bfa);
			~bf_args();
			bf_args& operator=(const bf_args& bfa);
			object** get_data() const;
			size_t get_size() const;
		protected:
			object** data;
			size_t size;
	};
}