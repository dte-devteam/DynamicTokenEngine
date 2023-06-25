#pragma once
#include "value.h"
namespace tokenoperator::dte_token::data {
	struct smart_object_pointer : value<object*>{
		public:
			smart_object_pointer(object* pointer = nullptr, uint64_t ID = 0);
			smart_object_pointer(const smart_object_pointer& sop);
			~smart_object_pointer();
			smart_object_pointer& operator=(const smart_object_pointer& sop);
			smart_object_pointer& operator=(object* pointer);
			bool operator==(const smart_object_pointer& sop);
			operator object*() const;
			object* operator*() const;
			object* operator->() const;
			size_t get_owner_num() const;
		protected:
			size_t* owner_num;
	};
}