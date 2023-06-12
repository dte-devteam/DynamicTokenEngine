#pragma once
#include "value.h"
#include "scope_path.h"
namespace tokenoperator::dte_token::data {
	//it reserves memory for pointers (their ammount! if overflow, will realocate array of pointers and extend)
	//it doesn`t know anything about objects, except for their ID
	//store object*, but can`t delete, copy or create
	struct scope : value<object**> {
		public:
			scope(size_t size, size_t prefered_size, uint64_t ID = 0);
			scope(const scope& sc);
			~scope();
			void resize_to_prefered_size();
			void add_object(object* obj);
			bool remove_object(uint64_t ID = 0);
			object* get_object(scope_path s, size_t shift = 0);
			object* operator[](uint64_t ID);
			size_t get_size();
			size_t get_prefered_size();
		protected:
			size_t size;
			size_t prefered_size;
	};
}