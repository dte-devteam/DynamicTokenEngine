#pragma once
#include <iostream>
#include "path.h"
namespace dte_token {
	struct stream_data;
	typedef dte_utils::dynamic_array<object_handler> args;
	typedef void (*function)(stream_data&, args&);
	typedef object* (*global_get_object)(path&);
	typedef object* (*global_register_module)(path&);
	struct stream_data {
		//create stream by function (to do add constructor for stream caller
		//create stream by builder
		//suspend stream
		//kill stream
	};
	inline void test(stream_data& sd, args& args) {
		for (object* o : args) {
			std::cout << o;
			if (o) {
				std::cout << "\t" << o->ID;
			}
			std::cout << std::endl;
		}
	}
	inline function _fp = test;
}