#pragma once
#include "token/include/function.h"
#include "module_unit.h"
#include "core/include/type_assembler.h"
namespace dte_core {
	class module_assembler {
		public:
			SINGLETON(module_assembler)
			//void init();
			static void register_module(dte_module::module_instance* mi);
			static void remove_module(size_t virtual_name) {}//to do
		private:
			dte_utils::dynamic_array<module_unit> modules;
			static dte_token::object* get_object(const dte_token::path& p);
			module_assembler() {}
	};
}