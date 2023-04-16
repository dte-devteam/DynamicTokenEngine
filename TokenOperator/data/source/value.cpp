#include "../include/value.h"
using namespace module;
namespace data {
	value::value(typedesc* type, void* pointer) : type(type), p(pointer) {}
	typedesc* value::gettypedesc() {
		return type;
	}
}