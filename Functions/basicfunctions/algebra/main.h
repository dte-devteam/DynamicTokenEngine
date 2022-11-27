#pragma once
#include "add/add.h"
#include "div/div.h"
#include "sub/sub.h"
#include "mul/mul.h"
namespace functions {
	namespace algebra {
		inline std::vector<basicfunction*>* dllfunctions = new std::vector<basicfunction*>(
			{
				&add::int_add,
				&add::float_add,
				&add::add,
				&sub::int_sub,
				&sub::float_sub,
				&mul::int_mul,
				&mul::float_mul,
				&div::int_div,
				&div::float_div
			}
		);
		std::vector<basicfunction*>* getfunctions() {
			return dllfunctions;
		}
	}
}