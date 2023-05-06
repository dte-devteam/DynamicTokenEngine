#include "../include/module_operator.h"
namespace module_operator {
	module_container* module_container::_instance;
	module_container* module_container::instance(std::vector<module_unit> modules) {
		if (!_instance) {
			_instance = new module_container(modules);
		}
		return _instance;
	}
	bool module_container::loadmodule(std::wstring dllname, std::wstring path, bool init_immedeatly, bool init_dependants) {
		return addgeneratedmodule(module::module(dllname, path), init_immedeatly, init_dependants);
	}
	bool module_container::addgeneratedmodule(module::module module, bool init_immedeatly, bool init_dependants) {
		for (module_unit& mu : modules) {
			if (mu.module_instance == module) {
				return false;
			}
		}
		modules.push_back({ module.requirements == nullptr, module });
		if (init_immedeatly) {
			initmodule(modules.back(), init_dependants);
		}
		return true;
	}
	void module_container::freemodule(std::wstring dllname, module::module_version minversion, module::module_version maxversion) {
		//to do: find all modules and unit+erase them
		//see some code from f() below, can be used
	}
	void module_container::initmodule(std::wstring dllname, bool init_dependants, module::module_version minversion, module::module_version maxversion) {
		for (module_unit& mu : modules) {
			if (mu.module_instance.getdllname() == dllname && mu.module_instance.getversion().in_range(minversion, maxversion)) {
				initmodule(mu, init_dependants);
			}
		}
	}
	module_container::module_container(std::vector<module_unit>& modules) : modules(modules){}
	void module_container::initmodule(module_unit& module, bool init_dependants) {
		//intiation can be called is requirements are not empty and pointer to them isn`t null
		if (!module.init_status) {
			//init modulespace (defines what modules can be used for initiation, contains indices)
			//modulespace is selected modules for initiation (can`t store module_unit&, but can store index/pointer to module_unit)
			std::vector<size_t> modulespace;
			initmodulespace(modulespace, module);
			initmoduleunit(modulespace, module);
		}
		if (init_dependants) {
			//IS TOO RAW, CAN DIE IN RECURSION
			//IS TOO RAW, TOO OVERLOADED
			for (module_unit& mu : modules) {
				if (!mu.init_status && mu.module_instance.requirements) {
					for (module::module_requirement& mr : *mu.module_instance.requirements) {
						if (mr.getname() == module.module_instance.getdllname() && module.module_instance.getversion().in_range(mr.getminversion(), mr.getmaxversion())) {
							initmodule(mu, init_dependants);
						}
					}
				}
			}
		}
	}
	void module_container::initmodulespace(std::vector<size_t>& modulespace, module_unit& module) {
		if (module.module_instance.requirements) {
			size_t size = modules.size();
			for (module::module_requirement& mr : *module.module_instance.requirements) {
				module::module_version min_v = mr.getminversion();
				module::module_version max_v = mr.getmaxversion();
				for (size_t i = 0; i < size; i++) {
					if (modules[i].module_instance.getdllname() == mr.getname()) {
						if (modules[i].module_instance.getversion().in_range(min_v, max_v)) {
							modulespace.push_back(i);
						}
						break;
					}
				}
			}
		}
	}
	void module_container::initmoduleunit(std::vector<size_t>& modulespace, module_unit& module) {
		bool module_init_status = true;
		if (module.module_instance.functions) {
			for (module::function_data& fd : *module.module_instance.functions) {
				bool init_status = true;
				bool stack_status = true;
				std::vector<size_t> inited_indeces;
				size_t size = fd.requirements.size();
				for (size_t i = 0; i < size && init_status; i++) {
					initexportrequirement(fd.requirements[i], modulespace, inited_indeces, init_status, stack_status, i);
				}
				fd.init_status = init_status;
				fd.stack_status = stack_status;
				module_init_status &= init_status & stack_status;
			}
		}
		//if (module.module_instance.types) {} //is realy needed?
		if (module.module_instance.data) {} //to do later, initiation looks like function initiation
		module.init_status = module_init_status;
	}
	void module_container::initexportrequirement(module::export_requirement& er, std::vector<size_t>& modulespace, std::vector<size_t>& inited_indeces, bool& init_status, bool& stack_status, size_t index) {
		//to do requirement init
	}
}