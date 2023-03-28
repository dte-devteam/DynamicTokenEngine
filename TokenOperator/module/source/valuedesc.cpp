#include "../include/valuedesc.h"
namespace module {
	valuedesc::valuedesc(typedesc* type, void* pointer) : type(type), p(pointer) {}
	typedesc* valuedesc::gettypedesc() {
		return type;
	}
}