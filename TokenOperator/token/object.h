#pragma once
#include <stdint.h>
class object {
	public:
		object(uint64_t id) : id(id) {}
		uint64_t getid() const {
			return id;
		}
		void free() {
			delete this;
		}
	protected:
		virtual ~object() {}
		uint64_t id;
};