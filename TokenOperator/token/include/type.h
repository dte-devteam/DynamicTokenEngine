#pragma once
#include "utils/include/text.h"
#include "utils/include/dynamic_array.h"
#include <xstring>
#define STR_TYPE(TYPE) #TYPE
#define STR_DECL_TYPE(INSTANCE) dte_token::typename_getter<decltype(INSTANCE)>()
namespace dte_token {
	template<typename T>
	auto typename_getter() noexcept {
		#if		defined(__clang__)
			auto func_name = std::string_view{ __PRETTY_FUNCTION__ };
			return func_name.substr(39, func_name.length() - 40); //"auto dte_token::typename_getter() [T = _T]" where _T is type name
		#elif	defined(__GNUC__)
			auto func_name = std::string_view{ __PRETTY_FUNCTION__ };
			return func_name.substr(53, func_name.length() - 54); //"auto dte_token::typename_getter() [with T = _T] where _T is type name"
		#elif	defined(_MSC_VER)
			auto func_name = std::string_view{ __FUNCSIG__ };
			return func_name.substr(40, func_name.length() - 56); //"auto __cdecl dte_token::typename_getter<T>(void) noexcept" where T is type name
		#else
		#error Unsupported compiler for compile-time type name generation
		#endif
	}
	//#define OPERATIONAL_TYPES(...) enum TYPE_REQUEST {__VA_ARGS__};
	struct type {
		const char*								name;				//user defined name for easier perfomance
		size_t									virtual_type;		//virtual type allowing getting data from object
		dte_utils::dynamic_array<type*>			parents;			//parents
		type(const char* type_name, size_t virtual_type = 0) : name(type_name), virtual_type(virtual_type) {}
		type(const type& other_type) : name(dte_utils::constexpr_strcpy(other_type.name)), virtual_type(other_type.virtual_type), parents(other_type.parents) {}
		type(type&& other_type) noexcept : name(std::move(other_type.name)), virtual_type(other_type.virtual_type), parents(std::move(other_type.parents)) {}
		~type() {
			//if you got _debugbreak() here - you used const char[]:
			//for const char[] in constructor apply constexpr_strcpy
			delete[] name;
		}
		bool is_same_as(const type& other_type) {
			return virtual_type == other_type.virtual_type;
		}
		bool is_parent_of(const type& other_type) {
			return false;	//to do
		}
		bool is_coherent_to(const type& other_type) {
			return !dte_utils::constexpr_strcmp(name, other_type.name);
		}
		//operators-----------------------------
		type& operator=(type&& other_type_handler) noexcept {
			if (this == &other_type_handler) {
				return *this;
			}
			name = std::move(other_type_handler.name);
			virtual_type = std::move(other_type_handler.virtual_type);
			parents = std::move(other_type_handler.parents);
			return *this;
		}
	};
	struct type_handler {
		const char*								name;				//user defined name for easier perfomance
		dte_utils::dynamic_array<const char*>	parents;			//other types name for polymorphism
		type*									type_instance;		//ponter to type
		type_handler(const char* name) : name(name), parents(), type_instance(nullptr) {}
		template<size_t N>
		type_handler(const char* name, const char* (&array)[N]) : name(name), parents(array, N, 0), type_instance(nullptr) {}
		type_handler(const char* name, const char** array, size_t array_size) : name(name), parents(array, array_size), type_instance(nullptr) {}
		type_handler(const type_handler& other_type_handler) : name(dte_utils::constexpr_strcpy(other_type_handler.name)), parents(other_type_handler.parents), type_instance(other_type_handler.type_instance) {}
		type_handler(type_handler&& other_type_handler) noexcept : name(std::move(other_type_handler.name)), parents(std::move(other_type_handler.parents)), type_instance(std::move(other_type_handler.type_instance)) {}
		~type_handler() {
			//if you got _debugbreak() here - you used const char[]:
			//for const char[] in constructor apply constexpr_strcpy
			delete[] name;
		}
		//operators-----------------------------
		operator type*() const {
			return type_instance;
		}
		type_handler& operator=(const type_handler& other_type_handler) {
			if (&other_type_handler == this) {
				return *this;
			}
			delete[] name;
			name = dte_utils::constexpr_strcpy(other_type_handler.name);
			parents = other_type_handler.parents;
			type_instance = other_type_handler.type_instance;
			return *this;
		}
		type_handler& operator=(type_handler&& other_type_handler) noexcept {
			if (&other_type_handler == this) {
				return *this;
			}
			delete[] name;
			name = std::move(other_type_handler.name);
			parents = std::move(other_type_handler.parents);
			type_instance = std::move(other_type_handler.type_instance);
			return *this;
		}
	};
}