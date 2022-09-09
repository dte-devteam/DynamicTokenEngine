#pragma once
#include "tokenfunction.h"
#include "defaultvalues.h"
namespace tokenfunction {
	namespace algebra {
		struct add : basicfunction {
			add();
			void execute(std::vector<argument> args) {
				std::vector<argument> values = filldefaultvalues(args);
				if (!args[0].valuepointer) {
					return; //error unable to convert
				}
				*(int*)values[2].valuepointer = *(int*)values[1].valuepointer + *(int*)values[0].valuepointer;
			}
		};
		static add addinstance{};
	}
}