#pragma once
#include "token/include/function.h"
#include "module/include/module_instance.h"
#include "core/include/type_assembler.h"
namespace dte_core {
	class module_assembler {
		public:
			SINGLETON(module_assembler)
			//void init();
		private:
			dte_token::dynamic_array<dte_module::module_instance*> modules;
			static dte_token::object* get_object(const dte_token::path& p);
			static void register_module() {}//to do
			static void remove_module() {}//to do
			module_assembler() {}
	};
}