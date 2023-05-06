#pragma once
#include "module_unit.h"
namespace module_operator {
	class module_container {
		public:
			static module_container* instance(std::vector<module_unit> modules = {});
			//module load/unload
			bool loadmodule(std::wstring dllname, std::wstring path = L"", bool init_immedeatly = false, bool init_dependants = true);
			bool addgeneratedmodule(module::module module, bool init_immedeatly = false, bool init_dependants = true);
			void freemodule(std::wstring dllname, module::module_version minversion = module::MIN_MODULE_VERSION, module::module_version maxversion = module::MAX_MODULE_VERSION);
			//module initiation
			void initmodule(std::wstring dllname, bool init_dependants = true, module::module_version minversion = module::MIN_MODULE_VERSION, module::module_version maxversion = module::MAX_MODULE_VERSION);
			void resetmoduleinitstatus(std::wstring dllname, module::module_version minversion = module::MIN_MODULE_VERSION, module::module_version maxversion = module::MAX_MODULE_VERSION);
		private:
			module_container(std::vector<module_unit>& modules);
			void initmodule(module_unit& module, bool init_dependants);
			void initmodulespace(std::vector<size_t>& modulespace, module_unit& module);
			void initmoduleunit(std::vector<size_t>& modulespace, module_unit& module);
			void initexportrequirement(module::export_requirement& er, std::vector<size_t>& modulespace, std::vector<size_t>& inited_indeces, bool& init_status, bool& stack_status, size_t index);
			static module_container* _instance;
			std::vector<module_unit> modules;
	};
}