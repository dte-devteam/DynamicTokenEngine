#include "../include/object.h"
namespace memory {
	namespace object {
		iterator::iterator(size_t typesize) : pointer(malloc(typesize)){}
		iterator::~iterator() {
			for (stream::stream* s : usedbystreams) {
				s->killstream(s);	//fix, make enough rights to kill;
			}
			free(pointer);
		}
		void* iterator::getpointer() {
			return pointer;
		}
		bool iterator::settype(uint64_t newtype) {
			if (isblocked) {
				return false;
			}
			type = newtype;
			return true;
		}
		uint64_t iterator::getid() {
			return id;
		}
		uint64_t iterator::gettype() {
			return type;
		}

		typeallocator::typeallocator(size_t typesize, size_t listsize) : typesize(typesize) {
			while (listsize > 0) {
				iters.push_back(new iterator(typesize));
				listsize--;
				//if (!iters.back()->pointer) {
				//	в случае ошибки - уничтожить
				//}
			}
		}
		typeallocator::~typeallocator() {
			for (iterator* i : iters) {
				i->isblocked = true;
				delete i;
			}
			iters.clear();
		}
		int typeallocator::setlistsize(size_t listsize, bool forced) {
			if (listsize < iters.size()) {
				if (forced) {
					for (size_t i = iters.size(); i > listsize; i--) {
						delete iters.back();
						iters.pop_back();
					}
					return 0;
				}
				return -1;	//fail to resize, no memory losses alowed
			}
			for (size_t i = iters.size(); i < listsize; i++) {
				iters.push_back(new iterator(typesize));
				//if (!iters.back()->pointer) {
				//	в случае ошибки - уничтожить
				//	return -2;	//fail to create memory
				// (to do)
				//}
			}
			return 0;
		}
		void typeallocator::unregisterobject(iterator* iter, stream::stream* caller) {
			if (caller) {
				iter->usedbystreams.erase(
					find_if(
						iter->usedbystreams.begin(), 
						iter->usedbystreams.end(), 
						[caller](stream::stream* stream) { 
							return caller->getid() == stream->getid(); 
						}
					)
				);
			}
			if (iter->usedbystreams.empty()) {
				iter->id = 0;
				iter->type = 0;
				iter->isblocked = false;
			}
		}
		iterator* typeallocator::addobject(uint64_t type, stream::stream* caller) {
			for (iterator* i : iters) {
				if (!i->id) {
					i->id = memorycontroller::instance()->getfreeid();
					i->type = type;
					i->isblocked = true;
					if (caller) {
						i->usedbystreams.push_back(caller);
						caller->iterators.push_back(i);
					}
					return i;
				}
			}
			return nullptr;
		}
		iterator* typeallocator::getobject(uint64_t id, bool maywrite, stream::stream* caller) {
			for (iterator* i : iters) {
				if (i->getid() == id) {
					if (i->isblocked && maywrite) {
						return nullptr;
					}
					if (maywrite) {
						i->isblocked = true;
					}
					if (caller) {
						if (find_if(i->usedbystreams.begin(), i->usedbystreams.end(),[caller](stream::stream* stream) { return caller->getid() == stream->getid(); }) == i->usedbystreams.end()) {
							i->usedbystreams.push_back(caller);
							caller->iterators.push_back(i);
						}
					}
					return i;
				}
			}
			return nullptr;
		}
		size_t typeallocator::gettypesize() {
			return typesize;
		}
		size_t typeallocator::getlistsize() {
			return iters.size();
		}

		void typeallocator::log_data(bool extended) {
			std::cout << "---start of memory block---" << typesize << std::endl;
			std::cout << "size of type:" << typesize << std::endl;
			std::cout << "size of list:" << getlistsize() << std::endl;
			size_t l = 0;
			for (iterator* i : iters) {
				std::cout << std::left << std::setw(8) << "index: ";
				std::cout << std::left << std::setw(8) << l;
				std::cout << std::left << std::setw(5) << "id: ";
				std::cout << std::left << std::setw(10) << i->id;
				std::cout << std::left << std::setw(7) << "type: ";
				std::cout << std::left << std::setw(10) << i->type;
				std::cout << std::left << std::setw(12) << "isblocked: ";
				std::cout << std::left << std::setw(5) << i->isblocked;
				if (extended) {
					std::cout << std::left << std::setw(10) << "pointer: ";
					std::cout << std::left << std::setw(20) << i->pointer;
					std::cout << std::left << std::setw(16) << "tread pointers: ";
					std::cout << i->usedbystreams.size();
				}
				std::cout << std::endl;
				l++;
			}
			std::cout << "---end of memory block---" << std::endl;
		}

		memorycontroller* memorycontroller::_instance;
		memorycontroller::memorycontroller(std::vector<size_t>* types) {
			if (types) {
				for (size_t iter : *types) {
					if (find_if(objects.begin(), objects.end(), [iter](typeallocator* alloc) { return iter == alloc->typesize; }) == objects.end()) {
						addtypeallocator(iter);
					}
				}
			}
		}
		memorycontroller::~memorycontroller() {
			for (typeallocator* ta : objects) {
				delete ta;
			}
			_instance = nullptr;
		}
		memorycontroller* memorycontroller::instance(std::vector<size_t>* sizes) {
			if (!_instance) {
				_instance = new memorycontroller(sizes);
			}
			return _instance;
		}
		void memorycontroller::addtypeallocator(size_t typesize, size_t listsize) {
			for (typeallocator* ta : objects) {
				if (ta->typesize) {
					ta->setlistsize(listsize, false);
					return;
				}
			}
			objects.push_back(new typeallocator(typesize, listsize));
		}
		void memorycontroller::deltypeallocator(size_t typesize) {
			std::vector<typeallocator*>::iterator iter = find_if(objects.begin(), objects.end(), [typesize](typeallocator* alloc) { return typesize == alloc->typesize; });
			if (iter != objects.end()) {
				delete (typeallocator*)*iter;
				objects.erase(iter);
			}
		}
		iterator* memorycontroller::getobject(uint64_t id, bool maywrite, stream::stream* caller) {
			iterator* iter;
			for (typeallocator* ta : objects) {
				iter = ta->getobject(id, maywrite, caller);
				return iter;
			}
			return nullptr;
		}
		uint64_t memorycontroller::getfreeid() {
			//to do
			return 20;
		}
		bool memorycontroller::hastypewithsize(size_t typesize) {
			for (typeallocator* ta : objects) {
				if (ta->typesize) {
					return true;
				}
			}
			return false;
		}
	}
}