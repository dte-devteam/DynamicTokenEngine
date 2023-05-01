#include "../include/module_operator.h"
namespace module_operator {
	module_container* module_container::_instance;
	module_container* module_container::instance(std::vector<module_unit> modules) {
		if (!_instance) {
			_instance = new module_container(modules);
		}
		return _instance;
	}
	bool module_container::loadmodule(std::wstring dllname, bool init_immedeatly) {
		return addgeneratedmodule(module::module(dllname), init_immedeatly);
	}
	bool module_container::addgeneratedmodule(module::module module, bool init_immedeatly) {
		std::vector<module_unit>::iterator end = modules.end();
		std::vector<module_unit>::iterator iter = find_if(
			modules.begin(),
			end,
			[&module](module_unit mu) {
				return module.getdllname() == mu.module_intance.getdllname();
			}
		);
		if (iter == end) {
			modules.push_back({ false, false, module });
			if (init_immedeatly) {
				initmodule(modules.back());
			}
			return true;
		}
		return false;
	}
	void module_container::freemodule(std::wstring dllname) {
		std::vector<module_unit>::iterator end = modules.end();
		std::vector<module_unit>::iterator iter = find_if(
			modules.begin(),
			end,
			[dllname](module_unit mu) {
				return dllname == mu.module_intance.getdllname();
			}
		);
		if (iter != end) {

			//uninit (to do)

			modules.erase(iter);
		}
	}
	module_container::module_container(std::vector<module_unit> modules) : modules(modules){}
	void module_container::initmodule(module_unit& module) {
		//intiation can be called is requirements are not empty and pointer to them isn`t null
		if (!module.init_status) {
			//init modulespace (defines what modules can be used for initiation, contains indices)
			std::vector<size_t> modulespace;
			initmodulespace(modulespace, module);

			//init (to do)

		}
	}
	void module_container::initmodulespace(std::vector<size_t>& modulespace, module_unit& module) {
		if (module.module_intance.requirements) {
			size_t size = modules.size();
			for (module::module_requirement& mr : *module.module_intance.requirements) {
				for (size_t i = 0; i < size; i++) {
					if (modules[i].module_intance.getdllname() == mr.getname()) {
						if (modules[i].module_intance.getversion() >= mr.getminversion() && mr.getmaxversion() >= modules[i].module_intance.getversion()) {
							modulespace.push_back(i);
						}
						break;
					}
				}
			}
		}
	}
}