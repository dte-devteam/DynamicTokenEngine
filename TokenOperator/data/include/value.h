#pragma once
#include "module/include/typedesc.h"
namespace data {
	class value {
		public:
			value(module::typedesc* type, void* pointer = nullptr);
			module::typedesc* gettypedesc();
			virtual void* getpointer(void* getter) = 0;
		protected:
			module::typedesc* type;
			void* p;
	};
}