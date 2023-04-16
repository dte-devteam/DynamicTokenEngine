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
		//to do
	}

}