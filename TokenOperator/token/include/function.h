#pragma once
#include "utils/include/pointer.h"
#include "utils/include/dynamic_array.h"
namespace dte_token {
	struct token;
	struct stream_data;
	typedef dte_utils::dynamic_array<dte_utils::strong_ref<token, false>> args;
	typedef size_t (*function)(args&);
	//typedef void (*function)(stream_data&, args&);
	struct stream_data {
		//create stream by function (to do add constructor for stream caller
		//create stream by builder
		//suspend stream
		//kill stream
	};
}