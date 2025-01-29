#pragma once
#include <new>	//to do - find out why fixes error C2661 with operator new
#include <type_traits>

#include <iostream>
namespace dte_utils {
	template<typename T>
	struct array_handler {
		template<typename U> friend struct array_handler;
		size_t			as;		//allocated size
		size_t			us;		//used size
		T*				a;		//array
		void*			p;		//real array pointer (alignment)
		
	};


	//to do: handle malloc(N) = NULL (memory shortage) 
	template<typename T>
	struct dynamic_array {
		template<typename U> friend struct dynamic_array;
	}
}