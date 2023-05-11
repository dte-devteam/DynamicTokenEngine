#pragma once
#include "../../object.h"
#include "module/include/typedesc.h"
namespace data {
	class value : object {
		public:
			value(uint64_t id, module::typedesc* type, void* pointer = nullptr);
			module::typedesc* gettypedesc();
			virtual void* getpointer(void* getter) = 0;
		protected:
			module::typedesc* type;
			void* p;
	};
}