#pragma once
namespace module {
	enum class desc_type {
		function,	//pointer for direct work with f()
		f_call,		//pointer for calling f() (NOT FOR basicfunction!!!)
		f_mux,		//pointer for mux function (ONLY FOR muxfunction!!!)
		data,		//pointer for data
		type		//pointer for type data
	};
}