#pragma once
#include "utils/include/text.h"
#include <xstring>
#define STR_TYPE(TYPE) #TYPE
#define STR_DECL_TYPE(INSTANCE) dte_token::typename_getter<decltype(INSTANCE)>()
namespace dte_token {
	template<typename T>
	constexpr auto typename_getter() noexcept {
		#if		defined(__clang__)
			constexpr auto func_name = std::string_view{ __PRETTY_FUNCTION__ };
			return func_name.substr(39, func_name.length() - 40); //"auto dte_token::typename_getter() [T = _T]" where _T is type name
		#elif	defined(__GNUC__)
			constexpr auto func_name = std::string_view{ __PRETTY_FUNCTION__ };
			return func_name.substr(53, func_name.length() - 54); //"constexpr auto dte_token::typename_getter() [with T = _T] where _T is type name"
		#elif	defined(_MSC_VER)
			constexpr auto func_name = std::string_view{ __FUNCSIG__ };
			return func_name.substr(40, func_name.length() - 56); //"auto __cdecl dte_token::typename_getter<T>(void) noexcept" where T is type name
		#else
		#error Unsupported compiler for compile-time type name generation
		#endif
	}
	//#define OPERATIONAL_TYPES(...) enum TYPE_REQUEST {__VA_ARGS__};
	struct type {
		const char*			name;				//user defined name for easier perfomance
		size_t				virtual_type;		//virtual type allowing getting data from object
		constexpr type(const char* type_name) : name(type_name), virtual_type(0) {}
		constexpr type(const type& other_type) : name(dte_utils::constexpr_strcpy(other_type.name)), virtual_type(other_type.virtual_type) {}
		constexpr ~type() {
			delete name;
		}
		constexpr bool is_same_as(const type& other_type) {
			return virtual_type == other_type.virtual_type;
		}
		constexpr bool is_parent_of(const type& other_type) {
			return false;	//to do
		}
		constexpr bool is_coherent_to(const type& other_type) {
			return !dte_utils::constexpr_strcmp(name, other_type.name);
		}
	};
}