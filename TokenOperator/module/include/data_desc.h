#pragma once
#include <stdint.h>
#include "token_data.h"
namespace data_desc {
	class typedesc {
		friend bool operator ==(typedesc& desc, uint32_t& supertype);
		friend bool operator ==(typedesc& desc, uint64_t& type);
		public:
			typedesc(uint32_t type = 0, size_t size = 0);
			uint32_t getsupertype();
			uint64_t gettype(uint32_t flags = 0);
			size_t getsize();
		protected:
			uint32_t supertype;
			size_t size;
	};
	class valuedesc {
		public:
			valuedesc(typedesc type, void* pointer = nullptr);
			typedesc gettypedesc();
			virtual void* getpointer(void* getter) = 0;
		protected:
			typedesc type;
			void* p;
	};
	struct vardesc : valuedesc {
		using valuedesc::valuedesc;
		void* getpointer(void* getter = nullptr);
	};
	struct constdesc : valuedesc {
		using valuedesc::valuedesc;
		void* getpointer(void* getter = nullptr);
	};
}