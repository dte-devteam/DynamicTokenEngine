#pragma once
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <variant>
/*
* function hierarchy:
* basicfunction
* |
* +-- function
*	  |
*	  +-- typedfunction
*	  |   |
*	  |   +-- muxfunction
*	  |   +-- cyclefuncton
*     +-- unreliablefunction
*	  +-- triggeredfunction
*	  +-- cyclefunction
* 
* error codes:
* 0 - no error, but if error occure - it will have no handler
* 1 - no error, but if error occure - it will have handler, so function don`t have to call-check and than call-execute
* 
* function data:
* defaultvalues - args, that we can put in function
* immunevalues - values, that are defined by function creation, no arg can change it
* 
* type structure:
* 32 bites - real type
* 32 bites - type description
* [0] - is const
* [1] - is pointer
* 
*/
namespace functionfactory {
	int test();
	struct basicfunction {
		basicfunction(uint64_t name = 0, std::vector<void*> defaultvalues = {});
		virtual ~basicfunction() {}
		uint64_t name;
		std::vector<void*> defaultvalues;
		virtual void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) = 0;
		protected:
			void filldefaultvalues(std::vector<void*>* argumentspointer, std::vector<void*>* target);
	};
	struct functioncaller {
		basicfunction* functionpointer;
		std::vector<std::pair<size_t, bool>> args_indices;
	};
	struct function : basicfunction {
		function(uint64_t name = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {});
		std::vector<functioncaller> callings;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool callfunctions(std::vector<void*>* values, uint64_t* errorcodepointer, bool forced);
	};
	struct typedfunction : function {
		typedfunction(uint64_t name = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, std::vector<std::vector<void*>> valuetypes = {});
		std::vector<std::vector<void*>> valuetypes;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool checktypecompability(std::vector<void*>* types);
			void filltypes(std::vector<void*>::iterator start, std::vector<void*>::iterator end, std::vector<void*>* target);
	};
	struct muxfunction : typedfunction {
		muxfunction(uint64_t name = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, std::vector<std::vector<void*>> valuetypes = {}, basicfunction* mux = nullptr);
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		basicfunction* mux;
	};
	struct unreliablefunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
	};
	struct triggeredfunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool check(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer);
	};
	struct cyclefunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
	};
}