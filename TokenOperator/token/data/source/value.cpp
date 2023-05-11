#include "../include/value.h"
using namespace module;
namespace data {
	value::value(uint64_t id, typedesc* type, void* pointer) : object(id), type(type), p(pointer) {}
	typedesc* value::gettypedesc() {
		return type;
	}
}