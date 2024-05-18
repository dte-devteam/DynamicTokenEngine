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
			std::string_view func_name(__PRETTY_FUNCTION__);
			return func_name.substr(39, func_name.length() - 40); //"auto dte_token::typename_getter() [T = _T]" where _T is type name
		#elif	defined(__GNUC__)
			std::string_view func_name(__PRETTY_FUNCTION__);
			return func_name.substr(53, func_name.length() - 54); //"auto dte_token::typename_getter() [with T = _T] where _T is type name"
		#elif	defined(_MSC_VER)
			std::string_view func_name(__FUNCSIG__);
			return func_name.substr(40, func_name.length() - 56); //"auto __cdecl dte_token::typename_getter<T>(void) noexcept" where T is type name
		#else
		#error Unsupported compiler for compile-time type name generation
		#endif
	}
	//#define OPERATIONAL_TYPES(...) enum TYPE_REQUEST {__VA_ARGS__};
	struct type {
		dte_utils::dynamic_wstring					name;
		/*dte_utils::dynamic_array<type*>			parents;
		bool is_same_as(const type& other_type) {
			return false;	//to do
		}
		bool is_parent_of(const type& other_type) {
			return false;	//to do
		}
		bool is_coherent_to(const type& other_type) {
			return false;	//to do
		}
		*/
		//operators-----------------------------
		/*
		type& operator=(type&& other_type_handler) noexcept {
			if (this == &other_type_handler) {
				return *this;
			}
			name = std::move(other_type_handler.name);
			parents = std::move(other_type_handler.parents);
			return *this;
		}
		*/
	};
}