#include "../include/object.h"
namespace memory {
	namespace object {
		iterator::iterator(size_t typesize) : pointer(malloc(typesize)){}
		iterator::~iterator() {
			for (stream::stream* s : usedbystreams) {
				s->killstream(s);	//fix, make enough rights to kill;
			}
			if (deleter) {
				deleter(pointer);
			}
			free(pointer);
		}
		void* iterator::getpointer() {
			return pointer;
		}
		uint64_t iterator::getid() {
			return id;
		}
		uint64_t iterator::gettype() {
			return type;
		}
		void iterator::settype(stream::stream* caller, uint64_t newtype) {
			if (blocker) {
				if (!caller) {
					return;
				}
				if (caller->getid() != blocker->getid()) {
					return;
				}
			}
			type = newtype;
		}
		void iterator::setdeleter(stream::stream* caller, void (*deleter)(void*)) {
			if (blocker) {
				if (!caller) {
					return;
				}
				if (caller->getid() != blocker->getid()) {
					return;
				}
			}
			this->deleter = deleter;
		}
		void iterator::unregisterobject(stream::stream* caller) {
			if (caller) {
				std::vector< stream::stream*>::iterator end = usedbystreams.end();
				std::vector< stream::stream*>::iterator iter = find_if(
					usedbystreams.begin(),
					end,
					[caller](stream::stream* stream) {
						return caller->getid() == stream->getid();
					}
				);
				if (iter != end) {
					usedbystreams.erase(iter);
				}
				if (blocker) {
					if (caller->getid() == blocker->getid()) {
						blocker = nullptr;
					}
				}
			}
			if (usedbystreams.empty()) {
				id = 0;
				type = 0;
				iscriticalsection = false;
				if (deleter) {
					deleter(pointer);
				}
			}
		}

		typeallocator::typeallocator(size_t typesize, size_t listsize) : typesize(typesize) {
			while (listsize > 0) {
				iters.push_back(new iterator(typesize));
				listsize--;
				//if (!iters.back()->pointer) {
				//	� ������ ������ - ����������
				//}
			}
		}
		typeallocator::~typeallocator() {
			for (iterator* i : iters) {
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
				//	� ������ ������ - ����������
				//	return -2;	//fail to create memory
				// (to do)
				//}
			}
			return 0;
		}
		void typeallocator::unregisterobject(iterator* iter, stream::stream* caller) {
			if (iter) {
				iter->unregisterobject(caller);
			}
		}
		iterator* typeallocator::addobject(uint64_t type, bool maywrite, stream::stream* caller, uint64_t id, bool iscriticalsection) {
			if (!id) {
				return nullptr;
			}
			for (iterator* i : iters) {
				if (!i->id) {
					i->id = id;
					i->type = type;
					if (maywrite) {
						i->blocker = caller;
					}
					if (caller) {
						i->usedbystreams.push_back(caller);
						i->iscriticalsection = iscriticalsection;
						caller->iterators.push_back(i);
					}
					return i;
				}
			}
			return nullptr;
		}
		iterator* typeallocator::getobject(uint64_t id, bool maywrite, stream::stream* caller) {
			for (iterator* i : iters) {
				if (i->id == id) {
					if (i->iscriticalsection) {
						return nullptr;
					}
					if (i->blocker && maywrite) {
						if (!caller) {
							return nullptr;
						}
						if (i->blocker->getid() != caller->getid()) {
							return nullptr;
						}
					}
					if (maywrite) {
						i->blocker = caller;
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
				std::cout << std::left << std::setw(12) << i->id;
				std::cout << std::left << std::setw(7) << "type: ";
				std::cout << std::left << std::setw(12) << i->type;
				std::cout << std::left << std::setw(12) << "isblocked: ";
				std::cout << std::left << std::setw(5) << i->blocker;
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
				if (ta->typesize == typesize) {
					ta->setlistsize(listsize, false);
					return;
				}
			}
			objects.push_back(new typeallocator(typesize, listsize));
		}
		void memorycontroller::deltypeallocator(size_t typesize) {
			std::vector<typeallocator*>::iterator iter = find_if(objects.begin(), objects.end(), [typesize](typeallocator* alloc) { return typesize == alloc->typesize; });
			if (iter != objects.end()) {
				delete *iter;
				objects.erase(iter);
			}
		}
		iterator* memorycontroller::addobject(uint64_t type, bool maywrite, stream::stream* caller, size_t size) {
			mutex.lock();
			uint32_t realtype = type >> 32;
			std::vector<table::typedesc>::iterator i = std::find_if(
				table::type_table.begin(), 
				table::type_table.end(), 
				[realtype](table::typedesc t) { 
					return realtype == t.type; 
				}
			);
			if (i == table::type_table.end()) {
				if (size) {
					uint64_t id = getfreeid();
					objects.push_back(new typeallocator(size, 1));
					table::registernewtype(realtype, size);
					mutex.unlock();
					return objects.back()->addobject(type, maywrite, caller, id);
				}
				mutex.unlock();
				return nullptr;
			}
			else {
				uint64_t id = getfreeid();
				std::vector<typeallocator*>::iterator ta = std::find_if(
					objects.begin(),
					objects.end(),
					[i](typeallocator* ta) {
						return i->size == ta->typesize;
					}
				);
				iterator* it = (*ta)->addobject(type, maywrite, caller, id);
				if (it) {
					mutex.unlock();
					return it;
				}
				else if (size) {
					(*ta)->setlistsize((*ta)->getlistsize() + 1, false);
					mutex.unlock();
					return (*ta)->addobject(type, maywrite, caller, id);
				}
				mutex.unlock();
				return nullptr;
			}
		}
		iterator* memorycontroller::getobject(uint64_t id, bool maywrite, stream::stream* caller) {
			iterator* iter;
			for (typeallocator* ta : objects) {
				iter = ta->getobject(id, maywrite, caller);
				if (iter) {
					return iter;
				}
			}
			return nullptr;
		}
		uint64_t memorycontroller::getfreeid() {
			uint64_t id = 1;
			for (typeallocator* ta : objects) {
				for (iterator* it : ta->iters) {
					if (id == it->getid()) {
						id++;
					}
				}
			}
			return id;
		}
	}
}