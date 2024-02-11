#pragma once
#include "utils/include/sigleton_defines.h"
#include "token/include/type.h"
namespace dte_core {
	class type_assembler {
		public:
			SINGLETON(type_assembler);
			void init(const dte_utils::dynamic_array<dte_token::type_handler>& array, size_t reserve = 0);
			dte_token::type* get_type(size_t virtual_type);
			dte_token::type* get_type(const char* name);
			static void register_type(dte_token::type_handler& type_to_add);
			static bool set_min_reserved_size(size_t reserved_size);
		private:
			dte_utils::dynamic_array<dte_token::type> types;
			type_assembler(){}
			size_t get_free_vir_type();
	};
}