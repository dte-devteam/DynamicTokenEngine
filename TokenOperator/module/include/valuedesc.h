#pragma once
#include "typedesc.h"
namespace module {
	class valuedesc {
		public:
			valuedesc(typedesc* type, void* pointer = nullptr);
			typedesc* gettypedesc();
			virtual void* getpointer(void* getter) = 0;
		protected:
			typedesc* type;
			void* p;
	};
}