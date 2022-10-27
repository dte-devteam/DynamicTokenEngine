#include "../include/object.h"
namespace memory {
	namespace object {
		typeallocator::typeallocator(size_t typesize, size_t listsize) : typesize(typesize), listsize(listsize) {
			memoryblock = malloc(typesize * listsize);
			objdesc = new iterator[listsize];
			iterator* end = objdesc + listsize;
			size_t addr = (size_t)memoryblock;
			for (iterator* i = objdesc; i < end; i++) {
				i->pointer = (void*)addr;
				addr += typesize;
			}
		}
		typeallocator::~typeallocator() {
			delete memoryblock;
			iterator* end = objdesc + listsize;
			for (iterator* i = objdesc; i < end; i++) {
				for (stream::stream* s : i->usedbystreams) {
					s->killstream(0);	//id нужно найти
				}
			}
			delete objdesc;
		}
		int typeallocator::setlistsize(size_t listsize, bool forced) {
			//not done, memory unbounding error
			//суть алгоритма:
			//останавливаем все потоки, которые имеют данные в этом блоке
			//перемещаем память
			//обновляем на нее указатели
			//возвращаем потоки к жизни
			if (listsize < this->listsize) {
				if (!forced) {
					return -1;	//fail to resize, because it will delete some objects
				}
			}
			iterator* end = objdesc + this->listsize;
			for (iterator* i = objdesc; i < end; i++) {
				for (stream::stream* s : i->usedbystreams) {
					if (s) {
						s->interrupt(0);
					}
				}
			}
			void* mem = realloc(memoryblock, typesize * listsize);
			if (mem) {
				//создать новый массив iterator
				iterator* iters = (iterator*)realloc(objdesc, sizeof(iterator*) * listsize);
				if (!iters) {
					return -3;	//fail to resize, no available memory for this type desc
				}
				memoryblock = mem;
				//установить в 0 все новые элементы
				end = iters + listsize;
				for (iterator* i = iters + this->listsize; i < end; i++) {
					i->id = 0;
					i->type = 0;
					i->isblocked = false;	//make atomic
					i->pointer = 0;
					i->usedbystreams = vector<stream::stream*>();
				}
				//оживить потоки
				for (iterator* i = objdesc; i < end; i++) {
					for (stream::stream* s : i->usedbystreams) {
						//stack потока нужно обновить (TO DO!!!)
						s->proceed(0);
					}
				}
				//удалить старый массив и указать новый
				delete objdesc;
				objdesc = iters;
				return 0;
			}
			return -2;	//fail to resize, no available memory for this type
		}
		void typeallocator::unregisterobject(iterator* iter) {
			size_t count = 0;
			iterator* end = objdesc + listsize;
			for (iterator* i = objdesc; i < end; i++) {
				if (i->type == iter->type) {
					count++;
				}
			}
			if (count < 2) {
				delgeneraltype(iter->type);
			}
			iter->id = 0;
		}
		iterator* typeallocator::addobject(uint64_t id, uint64_t type, stream::stream* caller) {
			iterator* end = objdesc + listsize;
			for (iterator* i = objdesc; i < end; i++) {
				if (!i->id) {
					i->id = id;
					i->type = type;
					i->isblocked = true;
					return i;
				}
			}
			return nullptr;
		}
		iterator* typeallocator::getobject(uint64_t id, bool maywrite, stream::stream* caller) {
			iterator* end = objdesc + listsize;
			for (iterator* i = objdesc; i < end; i++) {
				if (i->id == id) {
					if (i->isblocked && maywrite) {
						return nullptr;
					}
					if (maywrite) {
						i->isblocked = true;
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
			return listsize;
		}
		void typeallocator::addgeneraltype(uint64_t type) {
			uint32_t gentype = typemasker(type);
			if (std::find_if(generaltypes.begin(), generaltypes.end(), [gentype](uint32_t t) { return t == gentype; }) == generaltypes.end()) {
				generaltypes.push_back(gentype);
			}
		}
		void typeallocator::delgeneraltype(uint64_t type) {
			uint32_t gentype = typemasker(type);
			generaltypes.erase(std::find_if(generaltypes.begin(), generaltypes.end(), [gentype](uint32_t t) { return t == gentype; }));
		}
		uint32_t typeallocator::typemasker(uint64_t type) {
			type &= typemask;
			type = type >> 32;
			return (uint32_t)type;
		}

		void typeallocator::log_data() {
			std::cout << "size of type:" << typesize << std::endl;
			size_t l = 0;
			iterator* iter = objdesc;
			while (l < 100) {
				std::cout << std::left << std::setw(8) << "index: ";
				std::cout << std::left << std::setw(8) << l;
				std::cout << std::left << std::setw(5) << "id: ";
				std::cout << std::left << std::setw(10) << iter->id;
				std::cout << std::left << std::setw(7) << "type: ";
				std::cout << std::left << std::setw(10) << iter->type;
				std::cout << std::left << std::setw(12) << "isblocked: ";
				std::cout << std::left << std::setw(5) << iter->isblocked;
				std::cout << std::left << std::setw(10) << "pointer: ";
				std::cout << std::left << iter->pointer << std::endl;
				l++;
				iter++;
			}
			std::cout << "---end of memory block---" << typesize << std::endl;
		}

		memorycontroller* memorycontroller::_instance;
		memorycontroller::memorycontroller(vector<size_t>* types) {
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
				ta->~typeallocator();
			}
			_instance = nullptr;
		}
		memorycontroller* memorycontroller::instance(vector<size_t>* sizes) {
			if (!_instance) {
				_instance = new memorycontroller(sizes);
			}
			return _instance;
		}
		void memorycontroller::addtypeallocator(size_t typesize, size_t listsize) {
			objects.push_back(new typeallocator(typesize, listsize));
		}
		void memorycontroller::deltypeallocator(size_t typesize) {
			vector<typeallocator*>::iterator iter = find_if(objects.begin(), objects.end(), [typesize](typeallocator* alloc) { return typesize == alloc->typesize; });
			if (iter != objects.end()) {
				((typeallocator*)*iter)->~typeallocator();
				objects.erase(iter);
			}
		}
	}
}