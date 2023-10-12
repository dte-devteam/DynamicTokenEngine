#pragma once
#include "module_source_requirement.h"
#include "token/data/include/scope.h"
namespace tokenoperator::dte_module {
	struct module_source : dte_token::data::value<std::pair<dte_token::data::smart_pointer<dte_token::object>, bool>> {
		public:
			template<typename T>
			module_source(T* obj, module_source_requirement* requirements = nullptr, size_t requirement_num = 0, dte_token::data::scope_path path_to_set = dte_token::data::EMPTY_SCOPE_PATH(0), uint64_t ID = 0) : value<std::pair<dte_token::data::smart_pointer<dte_token::object>, bool>>(ID), init_status{ false, false }, requirement_num(requirement_num), requirements(new module_source_requirement[requirement_num]), path_to_set(path_to_set) {
				v.first = dte_token::data::smart_pointer<T>(obj);
				v.second = std::is_base_of<dte_token::data::scope, T>::value;
				size_t i = requirement_num;
				while (i) {
					this->requirements[i] = requirements[--i];
				}
			}
			module_source(const module_source& ms);
			bool get_init_status();
			bool get_stack_status();
			size_t get_requirement_num();
			module_source_requirement& operator[](size_t i);
			dte_token::data::scope_path* get_path_to_set();
		protected:
			bool init_status[2];	//init + stack
			size_t requirement_num;
			module_source_requirement* requirements;
			dte_token::data::scope_path path_to_set;
	};
}