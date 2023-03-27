#pragma once
#include <stdint.h>
//#include <atomic>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../../deletable_obj.h"
#define RAW_HAS_E *errorcodepointer > 1
#define RAW_HAS_CRIT_E *errorcodepointer > 2
#define HAS_E errorcodepointer ? RAW_HAS_E : false
#define HAS_CRIT_E errorcodepointer ? RAW_HAS_CRIT_E : false
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
* 1 - no error, but if error occure - it will have handler, so function don`t have to call-check and than call-execute, after "try" function
* 2 - no error, but execution must be stoped
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
* [2] - is class (list of pointers to another iterators)
*/
namespace functionfactory {
	int r();
	struct basicfunction {
		basicfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {});
		virtual ~basicfunction() {}
		uint64_t getid() const;
		std::vector<void*> defaultvalues;	//make this protected!
		virtual void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) = 0;
		protected:
			void filldefaultvalues(std::vector<void*>* argumentspointer, std::vector<void*> &target);
			uint64_t id;
	};
	struct functioncaller {
		constexpr functioncaller(basicfunction* functionpointer, std::vector<std::pair<size_t, bool>> args_indices) : functionpointer(functionpointer), args_indices(args_indices){}
		basicfunction* functionpointer;
		std::vector<std::pair<size_t, bool>> args_indices;
	};
	struct function : basicfunction {
		function(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {});
		std::vector<functioncaller> callings; //make this protected!
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		protected:
			bool callfunctions(std::vector<void*>& values, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct typedfunction : function {
		typedfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, std::vector<std::vector<void*>> valuetypes = {});
		std::vector<std::vector<void*>> valuetypes; //make this protected!
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		protected:
			virtual bool checktypecompability(std::vector<void*>* types);
			void filltypes(std::vector<void*>::iterator start, std::vector<void*>::iterator end, std::vector<void*>* target);
	};
	struct subtypedfunction : typedfunction {
		using typedfunction::typedfunction;
		protected:
			bool checktypecompability(std::vector<void*>* types);
	};
	struct muxfunction : function {
		muxfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, basicfunction* mux = nullptr);
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		basicfunction* mux; //make this private!
	};
	struct unreliablefunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct triggeredfunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		protected:
			virtual bool check(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer);
	};
	struct cyclefunction : function {
		using function::function;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
}