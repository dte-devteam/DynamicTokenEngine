#pragma once
#include "utils/include/pointer.h"
#include "utils/include/string.h"
#include <xstring>
#define STR_TYPE(TYPE) #TYPE
#define STR_DECL_TYPE(INSTANCE) dte_token::typename_getter<decltype(INSTANCE)>()
namespace dte_token {
	template<typename T>
	constexpr auto typename_getter() noexcept {
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
		dte_utils::dynamic_wstring							name;
		//operators-----------------------------
		type& operator=(const type& other_type) noexcept;
		type& operator=(type&& other_type) noexcept;
		bool operator==(const type& other_type) const noexcept;
	};
}