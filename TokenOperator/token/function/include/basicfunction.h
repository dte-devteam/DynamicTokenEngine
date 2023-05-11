#pragma once
#include <stdint.h>
//#include <atomic>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../../deletable_obj.h"
#include "../../object.h"
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
namespace function {
	struct basicfunction : object {
		basicfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {});
		std::vector<void*> defaultvalues;	//make this protected!
		virtual void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) = 0;
		protected:
			void filldefaultvalues(std::vector<void*>* argumentspointer, std::vector<void*> &target);
	};
}