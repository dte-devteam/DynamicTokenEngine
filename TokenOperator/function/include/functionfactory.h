#pragma once
#include <stdint.h>
#include <vector>
#include <algorithm>
/*
basicfunction->function->typedfunction->unreliablefunction(muxfunction)
									  ->muxfunction(unreliablefunction)
*/
namespace functionfactory {
	int test();
	struct basicfunction {
		uint64_t name;
		bool succeed;
		std::vector<void*> defaultvalues;
		virtual bool execute(std::vector<void*>* argumentspointer, bool errorpossible = true) = 0;
		protected:
			virtual std::vector<void*> filldefaultvalues(std::vector<void*>* argumentspointer);
	};
	struct functioncaller {
		basicfunction* functionpointer;
		std::vector<size_t> args_indices;
	};
	struct function : basicfunction {
		std::vector<functioncaller> callings;
		bool execute(std::vector<void*>* argumentspointer, bool errorhandeled);
	};
	struct typedfunction : function {
		std::vector<std::vector<void*>> valuetypes;
		bool execute(std::vector<void*>* argumentspointer, bool errorhandeled);
		protected:
			bool checktypecompability(std::vector<void*>* types);
	};
	struct muxfunction : typedfunction {
		bool execute(std::vector<void*>* argumentspointer, bool errorhandeled);
		protected:
			virtual size_t mux(std::vector<void*>* valuespointer, std::vector<void*>* typespointer) = 0;
	};
	struct unreliablefunction : typedfunction {

	};
}