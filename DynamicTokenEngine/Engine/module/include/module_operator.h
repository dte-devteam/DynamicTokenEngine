#pragma once
#include "module/include/module.h"
namespace module_operator {
	class module_container {
		public:
			static module_container* instance(std::vector<std::pair<bool, module::module>> modules = {});
			//module load/unload
			void loadmodule(std::wstring dllname);
			void addgeneratedmodule(module::module module, bool isinited = false);
			void freemodule(std::wstring dllname);
			//module data manupulation

		private:
			module_container(std::vector<std::pair<bool, module::module>> modules);
			static module_container* _instance;
			std::vector<std::pair<bool, module::module>> modules;
			bool inited;
			void initmodules();
			bool function_init_setter(module::function_data& function, module::function_requirement& f_require, bool& function_initiation, std::vector<module::module*>& require, void (*init_f)(module::function_data&, module::function_data&, module::function_requirement&));
			static void init_function_pointer(module::function_data& function_to_init, module::function_data& function_to_require, module::function_requirement& require_destination);
	};
}