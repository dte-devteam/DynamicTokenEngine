#pragma once
#include <stdint.h>
namespace tokenoperator::dte_token {
	struct object {
		public:
			object(uint64_t ID) : ID(ID){}
			virtual ~object() {}
			uint64_t getID() const { 
				return ID; 
			}
		protected:
			uint64_t ID;
	};
}