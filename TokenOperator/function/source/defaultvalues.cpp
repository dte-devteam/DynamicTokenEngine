#include "../include/defaultvalues.h"
namespace defaultvalues {
	defaultvalue::defaultvalue(size_t size, uint64_t name, void* pointer) : size(size), name(name) {
		p = pointer ? pointer : calloc(1, size);
	}
	defaultvalue::~defaultvalue() {
		free(p);
	}
	defaultvaluescontainer::defaultvaluescontainer(std::vector<defaultvalue*> defaultvalues) : defaultvalues(defaultvalues){}
	void defaultvaluescontainer::adddefaultvalue(defaultvalue* defaultvalue) {
		defaultvalues.push_back(defaultvalue);
		defvallist.push_back(std::pair<size_t, uint64_t>(defaultvalue->size, defaultvalue->name));
	}
	void defaultvaluescontainer::adddefaultvalues(std::vector<defaultvalue*>* defaultvalues) {
		for (defaultvalue* v : *defaultvalues) {
			adddefaultvalue(v);
		}
	}
	void* defaultvaluescontainer::getdefaultvalue(uint64_t name) {
		for (defaultvalue* v : defaultvalues) {
			if (v->name == name) {
				return v->p;
			}
		}
		return nullptr;
	}
	std::vector<std::pair<size_t, uint64_t>> defaultvaluescontainer::getdefvallist() {
		return defvallist;
	}
}