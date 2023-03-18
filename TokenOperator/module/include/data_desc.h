#pragma once
#include <stdint.h>
#include "token_data.h"
#include "deletable_obj.h"
namespace data_desc {
	class typedesc {
		friend bool operator ==(typedesc& desc, uint32_t& supertype);
		friend bool operator ==(typedesc& desc, uint64_t& type);
		public:
			typedesc(uint32_t supertype = 0, size_t size = 0, deletable_obj::DEL_F deleter = nullptr);
			uint32_t getsupertype() const;
			uint64_t gettype(uint32_t flags = 0) const;
			size_t getsize() const;
			void delete_obj(void* pointer) const;
		protected:
			uint32_t supertype;
			size_t size;
			deletable_obj::DEL_F deleter;
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