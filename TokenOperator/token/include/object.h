#pragma once
#include "dynamic_array.h"
#include "type.h"
namespace dte_token {
	struct object {
		friend struct object_handler;
		size_t					ID;		//ID
		type*					t;		//type
		void*					d;		//data
		size_t					h;		//handle num
		dynamic_array<object*>	b;		//branches
		dynamic_array<object*>	r;		//roots
		constexpr object(size_t ID = 0) : object(ID, nullptr, nullptr, {}, {}) {}
		constexpr object(size_t ID, type* type, void* data, dynamic_array<object*> branches, dynamic_array<object*> roots) : ID(ID), t(type), d(data), h(0), b(branches), r(roots) {}
		constexpr object(const object& obj, size_t ID = 0) : ID(ID), t(obj.t), d(obj.d), h(0) {}
		constexpr ~object() {
			delete d;
		}
		constexpr bool add_object(object* branch) {
			if (get_object(branch->ID)) {
				return false;
			}
			b.push_back(branch);
			branch->r.push_back(this);
			return true;
		}
		constexpr void remove_object(object* branch) {
			b.remove(branch);
			branch->r.remove(this);
			branch->try_killing();
		}
		constexpr object* get_object(size_t ID, bool forward = true) {
			object** o = forward ? b.find([ID](object* o) { return o->ID == ID; }) : r.find([ID](object* o) { return o->ID == ID; });
			return o ? *o : nullptr;
		}
		constexpr void* get_data(type* expected_type) const {
			//while there is no linker - let`s be safe
			if (!t) {
				return nullptr;
			}
			//----------------------------------------
			else if (t->is_same_as(*expected_type)) {
				return d;
			}
			else if (expected_type->is_parent_of(*t)) {
				return d;
			}
			return nullptr;
		}
		constexpr void set_data(void* data, type* new_type) {
			d = data;
			t = new_type;
		}
		constexpr void try_killing() {
			if (!(r.us + h)) {
				delete this;
			}
		}
	};
	struct object_handler {
		public:
			size_t				ID;		//ID
			constexpr object_handler(object* target = nullptr, size_t ID = 0) : ID(ID), target(target) {
				add_target();
			}
			constexpr object_handler(const object_handler& other_handler) : ID(other_handler.ID), target(other_handler.target) {
				add_target();
			}
			constexpr ~object_handler() {
				remove_target();
			}
			constexpr object_handler& operator=(const object_handler& handler) {
				if (this != &handler) {
					remove_target();
					target = handler.target;
					add_target();
				}
				return *this;
			}
			constexpr operator object*(){
				return target;
			}
		private:
			object*				target;	//pointer to object
			constexpr void add_target() {
				if (target) {
					++target->h;
				}
			}
			constexpr void remove_target() {
				if (target) {
					--target->h;
					target->try_killing();
				}
			}
	};
}