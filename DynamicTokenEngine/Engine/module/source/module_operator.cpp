#include "../include/module_operator.h"
namespace module_operator {
	module_container* module_container::_instance;
	module_container* module_container::instance(std::vector<std::pair<bool, module::module>> modules) {
		if (!_instance) {
			_instance = new module_container(modules);
		}
		return _instance;
	}
	void module_container::loadmodule(std::wstring dllname) {
		module::module m = module::module(dllname);
		if (m.getlibrary()) {
			modules.push_back({ m.requirements->size() == 0, m });
			//initmodules();
		}
	}
	void module_container::addgeneratedmodule(module::module module, bool isinited) {
		modules.push_back({ isinited, module });
		//initmodules();
	}
	void module_container::freemodule(std::wstring dllname) {
		std::vector<std::pair<bool, module::module>>::iterator end = modules.end();
		std::vector<std::pair<bool, module::module>>::iterator iter = find_if(
			modules.begin(),
			end,
			[dllname](std::pair<bool, module::module> m) {
				return dllname == m.second.getdllname();
			}
		);
		if (iter != end) {
			//uninit ��������� ������� (to do)
			iter->second.~module();
			modules.erase(iter);
		}
	}
	module_container::module_container(std::vector<std::pair<bool, module::module>> modules) : modules(modules), inited(modules.size() == 0){}
	void module_container::initmodules(){
		for (std::pair<bool, module::module>& module : modules) {
			if (!module.first) {
				std::vector<module::module*> require;
				bool module_initiation = true;
				std::vector<std::pair<bool, module::module>>::iterator end = modules.end();
				for (module::module_requirement& other_module : *module.second.requirements) {
					std::vector<std::pair<bool, module::module>>::iterator iter = find_if(
						modules.begin(),
						end,
						[&other_module](std::pair<bool, module::module> m) {
							return other_module.getname() == m.second.getdllname() && !(other_module.getminversion() > m.second.getversion());
						}
					);
					if (iter != end) {
						require.push_back(&iter->second);
					}
				}


				for (module::function_data& function : *module.second.functions) {
					if (!function.init_status) {
						bool function_initiation = true;
						for (module::function_requirement& f_r : function.requirements) {
							if (function_initiation) {
								//to do
								switch (f_r.getdesctype()) {
									case module::desc_type::function:
										if (function_init_setter(function, f_r, function_initiation, require, init_function_pointer)) {
											module_initiation = false;
										}
										break;
									default:
										function_initiation = false;
										break;
								}
							}
							else {
								break;
							}
						}
						function.init_status = function_initiation;
					}
				}
				module.first = module_initiation;
			}
		}
	}
	bool module_container::function_init_setter(module::function_data& function, module::function_requirement& f_require, bool& function_initiation, std::vector<module::module*>& require, void (*init_f)(module::function_data&, module::function_data&, module::function_requirement&)) {
		for (module::module* module : require) {
			for (module::function_data& r_function : *module->functions) {
				if (r_function.function->getid() == f_require.getname()) {
					init_f(function, r_function, f_require);
					return false;
				}
			}
		}
		function_initiation = false;
		return true;
	}
	void module_container::init_function_pointer(module::function_data& function_to_init, module::function_data& function_to_require, module::function_requirement& require_destination) {
		function_to_init.function->defaultvalues[require_destination.getindex()] = function_to_require.function;
	}
}