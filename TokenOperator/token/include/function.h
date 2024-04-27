#pragma once
#include <iostream>
namespace dte_token {
	struct stream_data;
	typedef dte_utils::dynamic_array<dte_utils::strong_ref<object, false>> args;
	typedef void (*function)(stream_data&, args&);
	struct stream_data {
		//create stream by function (to do add constructor for stream caller
		//create stream by builder
		//suspend stream
		//kill stream
	};
	inline void test(stream_data& sd, args& args) {
		for (dte_utils::strong_ref<object, false>& o : args) {
			std::cout << o.get_pointer();
			if (o.get_strong_owners()) {
				std::wcout << L"\t" << o->name.begin();
			}
			std::cout << std::endl;
		}
	}
	inline function _fp = test;
}