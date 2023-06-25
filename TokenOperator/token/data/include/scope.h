#pragma once
#include "smart_object_pointer.h"
#include "scope_path.h"
namespace tokenoperator::dte_token::data {
	//it reserves memory for pointers (their ammount! if overflow, will realocate array of pointers and extend)
	//it doesn`t know anything about objects, except for their ID
	//store object*, but can`t delete, copy or create
	struct scope : value<std::pair<smart_object_pointer, bool>*> {
		public:
			scope(size_t size, size_t prefered_size, uint64_t ID = 0);
			scope(const scope& sc);
			~scope();
			void resize_to_prefered_size();
			bool add_object(smart_object_pointer obj, bool is_base_of_scope = false);
			bool remove_object(uint64_t ID = 0);
			smart_object_pointer get_object(scope_path sp, size_t shift = 0);
			smart_object_pointer operator[](uint64_t ID);
			scope& operator=(const scope& sñ);
			size_t get_size();
			size_t get_prefered_size();
		protected:
			size_t size, prefered_size;
	};
}