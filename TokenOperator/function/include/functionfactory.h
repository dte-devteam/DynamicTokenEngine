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
using namespace std;
namespace functionfactory {
	int r();
	struct basicfunction {
		basicfunction(uint64_t name = 0, vector<void*> defaultvalues = {});
		virtual ~basicfunction() {}
		uint64_t name;
		vector<void*> defaultvalues;
		virtual void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) = 0;
		protected:
			void filldefaultvalues(vector<void*>* argumentspointer, vector<void*>* target);
	};
	struct functioncaller {
		basicfunction* functionpointer;
		vector<pair<size_t, bool>> args_indices;
	};
	struct function : basicfunction {
		function(uint64_t name = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {});
		vector<functioncaller> callings;
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool callfunctions(vector<void*>* values, uint64_t* errorcodepointer, bool forced);
	};
	struct typedfunction : function {
		typedfunction(uint64_t name = 0, vector<void*> defaultvalues = {}, vector<functioncaller> callings = {}, vector<vector<void*>> valuetypes = {});
		vector<vector<void*>> valuetypes;
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool checktypecompability(vector<void*>* types);
			void filltypes(vector<void*>::iterator start, vector<void*>::iterator end, vector<void*>* target);
	};
	struct muxfunction : typedfunction {
		muxfunction(uint64_t name = 0, vector<void*> defaultvalues = {}, vector<functioncaller> callings = {}, vector<vector<void*>> valuetypes = {}, basicfunction* mux = nullptr);
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		basicfunction* mux;
	};
	struct unreliablefunction : function {
		using function::function;
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
	};
	struct triggeredfunction : function {
		using function::function;
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
		protected:
			bool check(vector<void*>* argumentspointer, uint64_t* errorcodepointer);
	};
	struct cyclefunction : function {
		using function::function;
		void execute(vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced);
	};
}