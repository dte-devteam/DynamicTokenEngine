#pragma once
#include <stdint.h>
#include <vector>
#include "deletable_obj.h"
namespace defaultvalues {
	//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
	static size_t POINTER_SIZE = sizeof(void*);
	static const unsigned int UINT_ZERO = 0;
	static const unsigned long long ULL_ZERO = UINT_ZERO;
	static const void* NULL_PTR = nullptr;



	class defaultvalue {
		friend class defaultvaluescontainer;
		public:
			defaultvalue(size_t size, uint64_t name, void* pointer = nullptr);
			~defaultvalue();
		private:
			size_t size;
			uint64_t name;
			void* p;
	};
	class defaultvaluescontainer {
		//add values (by one/by vector) - to do
		public:
			defaultvaluescontainer(std::vector<defaultvalue*> defaultvalues);
			void adddefaultvalue(defaultvalue* defaultvalue);
			void adddefaultvalues(std::vector<defaultvalue*>* defaultvalues);
			void* getdefaultvalue(uint64_t name);
			std::vector<std::pair<size_t, uint64_t>> getdefvallist();
		private:
			std::vector<defaultvalue*> defaultvalues;
			std::vector<std::pair<size_t, uint64_t>> defvallist;
	};
}