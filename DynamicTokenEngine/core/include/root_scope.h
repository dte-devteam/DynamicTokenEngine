#pragma once
#include "core_module.h"
#include "token/data/include/scope.h"
#include "token/data/include/smart_pointer.h"
namespace dte_core {
	inline tokenoperator::dte_token::data::smart_pointer<tokenoperator::dte_token::data::scope> root_scope;
	inline void init_root_scope(size_t size, size_t prefered_size, uint64_t ID);
}