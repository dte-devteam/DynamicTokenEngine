#pragma once
namespace tokenoperator::dte_token {
	enum super_type {
		UNKNOWN		= 0x0,
		TYPE		= 0x1,
		VALUE		= 0x2,
		SCOPE		= 0x4,
		FUNCTION	= 0x8,
		STREAM		= 0x16
		//may be modules 3x? to do
		//
		//
	};
	template<typename T> constexpr inline
	super_type define_super_type() {
		super_type result = UNKNOWN;
		//to do
		//if (std::is_base_of<data::scope, T>::value) {
		//	result |= SCOPE
		//}
		return result;
	}
}