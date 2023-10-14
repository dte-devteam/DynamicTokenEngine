#pragma once
#include "token/data/include/scope.h"
#include "token/data/include/smart_pointer.h"
#include "core_module.h"
namespace dte_core {
	//to do add module metadata
	inline tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_token::data::scope> root_scope;
	void init_root_scope(size_t size, size_t prefered_size, uint64_t ID, tokenoperator::dte_token::stream::basic_stream& caller);
}