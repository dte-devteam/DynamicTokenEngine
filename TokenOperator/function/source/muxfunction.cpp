#include "../include/muxfunction.h"
namespace function {
	muxfunction::muxfunction(uint64_t id, std::vector<void*> defaultvalues, std::vector<functioncaller> callings, basicfunction* mux) : function(id, defaultvalues, callings), mux(mux) {}
	void muxfunction::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
		size_t size = defaultvalues.size();
		size_t argssize = argumentspointer->size();
		std::vector<void*> values;
		filldefaultvalues(argumentspointer, values);
		size_t index = callings.size();
		std::vector<void*> mux_args{ &index };
		std::copy(argumentspointer->begin() + values.size() - 1, argumentspointer->end(), std::back_inserter(mux_args));
		mux->execute(&mux_args, errorcodepointer, forced, stream);
		if (HAS_E) {
			return;
		}
		if (index < callings.size()) {
			std::vector<void*> args;
			for (std::pair<size_t, bool>& p : callings[index].args_indices) {
				if (p.second) {
					args.push_back((void*)p.first);
				}
				else {
					args.push_back(values[p.first]);
				}
			}
			callings[index].functionpointer->execute(&args, errorcodepointer, forced, stream);
		}
	}
}