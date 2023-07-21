#include "../include/root_scope.h"
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::function;
namespace dte_core {
	void init_root_scope(size_t size, size_t prefered_size, uint64_t ID) {
		root_scope = new scope(size + 1, prefered_size + 1, ID);
		//to do add dte module
		*core_module_info = { core_module_sources, ARRAYSIZE(core_module_sources) };
		//((basic_function*)(*core_module_sources[0]).get_pointer())->execute(); //to do (load core_module_info)
	}
}