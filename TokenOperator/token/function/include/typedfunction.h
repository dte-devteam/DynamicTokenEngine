#pragma once
#include "function.h"
namespace function {
	struct typedfunction : function {
		typedfunction(uint64_t id = 0, std::vector<void*> defaultvalues = {}, std::vector<functioncaller> callings = {}, std::vector<std::vector<void*>> valuetypes = {});
		std::vector<std::vector<void*>> valuetypes; //make this protected!
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		protected:
			virtual bool checktypecompability(std::vector<void*>* types);
			void filltypes(std::vector<void*>::iterator start, std::vector<void*>::iterator end, std::vector<void*>* target);
	};
}