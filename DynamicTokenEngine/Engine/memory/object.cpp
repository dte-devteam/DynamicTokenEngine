#include "object.h"
namespace memory {
	namespace object {
		iterator::iterator() : typeinstance(nullptr), id(0), flags(0), iscriticalsection(false), pointer(nullptr) {}
		iterator::iterator(stream::stream* caller, data_desc::typedesc* typeinstance, uint64_t id, uint32_t flags, bool iscriticalsection) : typeinstance(typeinstance), id(id), flags(flags), iscriticalsection(iscriticalsection){
			usedbystreams.push_back(caller);
			if (caller->maywrite) {
				blocker = caller;
			}
			create_value(typeinstance);
		}
		iterator::~iterator() {
			kill_value();
		}
		void* iterator::getpointer(stream::stream* caller) {
			return pointer;
		}
		uint64_t iterator::getid() {
			return id;
		}
		uint64_t iterator::gettype() {
			return typeinstance ? typeinstance->gettype(flags) : 0;
		}
		uint32_t iterator::getsupertype() {
			return typeinstance ? typeinstance->getsupertype() : 0;
		}
		uint32_t iterator::getflags() {
			return flags;
		}
		void iterator::settype(stream::stream* caller, data_desc::typedesc* typeinstance) {
			if (blocker) {
				if (!caller) {
					return;
				}
				if (caller->getid() != blocker->getid()) {
					return;
				}
			}
			this->typeinstance = typeinstance;
		}
		void iterator::setflags(stream::stream* caller, uint32_t flags) {
			if (blocker) {
				if (!caller) {
					return;
				}
				if (caller->getid() != blocker->getid()) {
					return;
				}
			}
			this->flags = flags;
		}
		void iterator::unregisterobject(stream::stream* caller) {
			if (caller) {
				std::vector<stream::stream*>::iterator end = usedbystreams.end();
				std::vector<stream::stream*>::iterator iter = find_if(
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
						for (stream::stream* s : usedbystreams) {
							if (s->maywrite) {
								blocker = s;
								break;
							}
						}
						iscriticalsection = false;
					}
				}
			}
			if (usedbystreams.empty()) {
				kill_value();
				id = 0;
				flags = 0;
				typeinstance = nullptr;
				iscriticalsection = false;
			}
		}
		void iterator::create_value(data_desc::typedesc* typeinstance) {
			this->typeinstance = typeinstance;
			pointer = malloc(typeinstance->getsize());
		}
		void iterator::kill_value() {
			for (stream::stream* s : usedbystreams) {
				s->killstream(s);	//fix, make enough rights to kill!!!!!!!!!!!!!;
			}
			if (typeinstance) {
				typeinstance->delete_obj(pointer);
			}
			else {
				free(pointer);
			}
		}


		memorycontroller* memorycontroller::_instance;
		memorycontroller::memorycontroller(std::vector<std::pair<data_desc::typedesc*, size_t>>* initstartmemory) {
			if (initstartmemory) {
				for (std::pair<data_desc::typedesc*, size_t>& p : *initstartmemory) {
					std::vector<std::pair<size_t, std::vector<iterator>>>::iterator end = objects.end();
					std::vector<std::pair<size_t, std::vector<iterator>>>::iterator i = std::find_if(
						objects.begin(),
						end,
						[&p](std::pair<size_t, std::vector<iterator>> i_p) { return p.first->getsize() == i_p.first; }
					);
					size_t num_elements = p.second ? p.second : defaultlistsize;
					if (i == end) {
						objects.push_back(
							{
								p.first->getsize(),
								std::vector<iterator>(num_elements)
							}
						);
					}
					else {
						i->second.resize(i->second.size() + num_elements);
					}
				}
			}
		}
		memorycontroller::~memorycontroller() {
			_instance = nullptr;
		}
		memorycontroller* memorycontroller::instance() {
			if (!_instance) {
				_instance = new memorycontroller();
			}
			return _instance;
		}
		memorycontroller* memorycontroller::instance(std::vector<std::pair<data_desc::typedesc*, size_t>> initstartmemory) {
			if (!_instance) {
				_instance = new memorycontroller(&initstartmemory);
			}
			return _instance;
		}
		iterator* memorycontroller::addobject(data_desc::typedesc* typeinstance, uint32_t flags, stream::stream* caller, bool getascritical) {
			if (!caller) {
				return nullptr;
			}
			mutex.lock();
			size_t typesize = typeinstance->getsize();
			uint64_t freeid = getfreeid();
			std::vector<std::pair<size_t, std::vector<iterator>>>::iterator end = objects.end();
			std::vector<std::pair<size_t, std::vector<iterator>>>::iterator i = std::find_if(
				objects.begin(),
				end,
				[typesize](std::pair<size_t, std::vector<iterator>> it) { return it.first == typesize; }
			);
			if (i == end) {
				objects.push_back({ typesize, {{ caller, typeinstance, freeid, flags, getascritical }} });
			}
			else {
				std::vector<iterator>::iterator p_end = i->second.end();
				std::vector<iterator>::iterator p_i = std::find_if(
					i->second.begin(),
					p_end,
					[](iterator it) { return !it.id; }
				);
				if (p_i == p_end) {
					i->second.push_back({ caller, typeinstance, freeid, flags, getascritical });
					mutex.unlock();
					return &i->second.back();
				}
				else {
					p_i->blocker = caller;
					p_i->create_value(typeinstance);
					p_i->id = freeid;
					p_i->flags = flags;
					p_i->iscriticalsection = getascritical;
					mutex.unlock();
					return &*p_i;
				}
			}
			mutex.unlock();
			return nullptr;
		}
		iterator* memorycontroller::getobject(uint64_t id, size_t size, stream::stream* caller, bool getascritical) {
			bool maywrite = caller ? caller->maywrite : true;
			if (size) {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					if (size == p.first) {
						std::vector<iterator>::iterator end = p.second.end();
						std::vector<iterator>::iterator i = std::find_if(
							p.second.begin(),
							end,
							[id](iterator it) { return it.id == id; }
						);
						if (i == end) {
							return nullptr;
						}
						if (i->iscriticalsection) {
							if (!caller) {
								return nullptr;
							}
							if (caller->getid() != i->blocker->getid() && caller->maywrite) {
								return nullptr;
							}
						}
						else {
							if (!i->blocker && caller ? caller->maywrite : false) {
								i->blocker = caller;
								i->iscriticalsection = getascritical;
							}
						}
						return &*i;
					}
				}
			}
			else {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					std::vector<iterator>::iterator end = p.second.end();
					std::vector<iterator>::iterator i = std::find_if(
						p.second.begin(),
						end,
						[id](iterator it) { return it.id == id; }
					);
					if (i == end) {
						return nullptr;
					}
					return &*i;
				}
			}
			return nullptr;
		}
		void memorycontroller::setlistsize(size_t listsize, bool forced, size_t datasize) {
			std::cout << "ds:" << datasize << ":ls:" << listsize << ":f:" << forced << std::endl;
			if (datasize) {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					if (p.first == datasize) {
						if (p.second.size() < listsize || forced) {
							p.second.resize(listsize);
						}
						return;
					}
				}
			}
			else {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					if (p.second.size() < listsize || forced) {
						p.second.resize(listsize);
					}
				}
			}
		}
		void memorycontroller::log_size(bool extended, size_t size) {
			if (size) {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					if (p.first == size) {
						std::cout << "len: " << p.second.size() << std::endl;
						for (iterator i : p.second) {
							std::cout << "size: " << p.first;
							log_iterator(i, 0, extended);
						}
						return;
					}
				}
				std::cout << "no data with size: " << size << std::endl;
			}
			else {
				for (std::pair<size_t, std::vector<iterator>>& p : objects) {
					std::cout << "len: " << p.second.size() << std::endl;
					for (iterator i : p.second) {
						std::cout << "size: " << p.first;
						log_iterator(i, 16, extended);
					}
				}
			}
		}
		void memorycontroller::log_iterator(iterator& i, size_t shift, bool extended) {
				std::cout << std::left << std::setw(shift);
				std::cout << std::left << std::setw(5) << "id: ";
				std::cout << std::left << std::setw(12) << i.id;
				std::cout << std::left << std::setw(7) << "supertype: ";
				std::cout << std::left << std::setw(12) << i.getsupertype();
				std::cout << std::left << std::setw(12) << "isblocked: ";
				std::cout << std::left << std::setw(18);
				i.blocker ? std::cout << i.blocker : std::cout << "no";
				if (extended) {
					std::cout << std::left << std::setw(10) << "pointer: ";
					std::cout << std::left << std::setw(20) << i.pointer;
					std::cout << std::left << std::setw(16) << "tread pointers: ";
					std::cout << i.usedbystreams.size();
				}
				std::cout << std::endl;
		}
		uint64_t memorycontroller::getfreeid() {
			uint64_t id = 1;
			free_id_start_loop:
			for (std::pair<size_t, std::vector<iterator>>& p : objects) {
				for (iterator& i : p.second) {
					if (id == i.id) {
						id++;
						goto free_id_start_loop;
					}
				}
			}
			return id;
		}
	}
}