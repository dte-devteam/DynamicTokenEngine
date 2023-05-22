#pragma once
#include <stdint.h>
namespace tokenoperator::token {
	struct object {
		public:
			object(uint64_t ID) : ID(ID){}
			uint64_t getID() const { return ID; }
			void free() { delete this; }
		protected:
			virtual ~object(){}
			uint64_t ID;
	};
}