#pragma once
#include <stdint.h>
#include <vector>
#include "deletable_obj.h"
namespace data {
	//(to do) вынести из lib в DynamicTokenEngine в lib, что не будет использоваться dll (не плодить статики)
	//уже перенесено, скоро будет переподключено
	static size_t POINTER_SIZE = sizeof(void*);
	static const unsigned int UINT_ZERO = 0;
	static const unsigned long long ULL_ZERO = UINT_ZERO;
	static const void* NULL_PTR = nullptr;



	class staticdata {
		public:
			staticdata(size_t size, uint64_t name, void* pointer = nullptr);
			virtual ~staticdata();
			size_t getsize();
			uint64_t getname();
			void* getpointer();
		protected:
			size_t size;
			uint64_t name;
			void* p;
	};
}