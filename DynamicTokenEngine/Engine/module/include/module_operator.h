#pragma once
#include "module/include/module_desc.h"
namespace module_operator {
	class module_container {
		public:
			static module_container* instance(std::vector<std::pair<bool, module_desc::module>> modules = {});
			//module load/unload
			void loadmodule(std::wstring dllname);
			void addgeneratedmodule(module_desc::module module, bool isinited = false);
			void freemodule(std::wstring dllname);
			//module data manupulation

		private:
			module_container(std::vector<std::pair<bool, module_desc::module>> modules);
			static module_container* _instance;
			std::vector<std::pair<bool, module_desc::module>> modules;
			bool inited;
			void initmodules();
			bool function_init_setter(dependency_desc::function_data& function, dependency_desc::function_requirement& f_require, bool& function_initiation, std::vector<module_desc::module*>& require, void (*init_f)(dependency_desc::function_data&, dependency_desc::function_data&, dependency_desc::function_requirement&));
			static void init_function_pointer(dependency_desc::function_data& function_to_init, dependency_desc::function_data& function_to_require, dependency_desc::function_requirement& require_destination);
	};
}