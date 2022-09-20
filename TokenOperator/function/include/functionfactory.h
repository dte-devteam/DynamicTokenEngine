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
		std::vector<void*> defaultvalues;
		virtual void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer) = 0;
		protected:
			virtual std::vector<void*> filldefaultvalues(std::vector<void*>* argumentspointer);
	};
	struct functioncaller {
		basicfunction* functionpointer;
		std::vector<size_t> args_indices;
	};
	struct function : basicfunction {
		std::vector<functioncaller> callings;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer);
	};
	struct typedfunction : function {
		std::vector<std::vector<void*>> valuetypes;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer);
		protected:
			bool checktypecompability(std::vector<void*>* types);
	};
	struct muxfunction : typedfunction {
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer);
		protected:
			virtual size_t mux(std::vector<void*>* valuespointer, std::vector<void*>* typespointer) = 0;
	};
	struct unreliablefunction : typedfunction {

	};
}