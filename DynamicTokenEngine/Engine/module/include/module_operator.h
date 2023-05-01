#pragma once
#include "module_unit.h"
namespace module_operator {
	class module_container {
		public:
			static module_container* instance(std::vector<module_unit> modules = {});
			//module load/unload
			bool loadmodule(std::wstring dllname, bool init_immedeatly = false);
			bool addgeneratedmodule(module::module module, bool init_immedeatly = false);
			void freemodule(std::wstring dllname);
		private:
			module_container(std::vector<module_unit> modules);
			void initmodule(module_unit& module);
			void initmodulespace(std::vector<size_t>& modulespace, module_unit& module);
			
			static module_container* _instance;
			std::vector<module_unit> modules;
	};
}