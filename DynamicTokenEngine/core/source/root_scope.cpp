#include "../include/root_scope.h"
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::function;
using namespace tokenoperator::dte_token::stream;
namespace dte_core {
	void init_root_scope(size_t size, size_t prefered_size, uint64_t ID, stream* caller) {
		root_scope = new scope(size + 1, prefered_size + 1, ID);	//+1 is for core
		*core_module_info = { core_module_sources, ARRAYSIZE(core_module_sources) };
		tokenoperator::dte_token::object* core_pointer[] = { &core_module_info };
		bf_args args(ARRAYSIZE(core_pointer), core_pointer);
		((basic_function*)(*core_module_sources[2]).first.get_pointer())->execute(caller, &args, false);
	}
}