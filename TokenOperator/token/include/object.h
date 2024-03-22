#pragma once
#include "utils/include/dynamic_array.h"
#include "type.h"
#include "container.h"
namespace dte_token {
	struct object {
		/*
		*	can`t be copied, because of container
		*/
		//friend struct object_handler;
		size_t					ID;		//ID
		type*					t;		//type handler
		container				c;		//data container
		size_t					h;		//handle num (does not really works, to do, after move every hadlers points to garbage)
		dte_utils::dynamic_array<object*>	b;		//branches
		dte_utils::dynamic_array<object*>	r;		//roots
		object(size_t ID = 0) : object(ID, nullptr, nullptr, {}, {}) {}
		object(size_t ID, type* type, void* data, dte_utils::dynamic_array<object*> branches, dte_utils::dynamic_array<object*> roots) : ID(ID), t(type), c(), h(0), b(branches), r(roots) {}
		object(const object&) = delete;
		object(object&& obj) noexcept : ID(std::move(obj.ID)), t(std::move(obj.t)), c(std::move(obj.c)), h(std::move(obj.h)) {}
		bool add_object(object* branch) {
			if (get_object(branch->ID)) {
				return false;
			}
			b.push_back(branch);
			branch->r.push_back(this);
			return true;
		}
		void remove_object(object* branch) {
			//b.remove(branch);
			//branch->r.remove(this);
			branch->try_killing();
		}
		object* get_object(size_t ID, bool forward = true) {
			object** o = forward ? b.find([ID](object* o) { return o->ID == ID; }) : r.find([ID](object* o) { return o->ID == ID; });
			return o ? *o : nullptr;
		}
		void* get_data_strictly(type* expected_type) const {
			//while there is no linker - let`s be safe
			if (!t) {
				return nullptr;
			}
			//----------------------------------------
			if (t->is_same_as(*expected_type)) {
				return c;
			}
			return nullptr;
		}
		void* get_data_polymorphic(type* expected_type) const {
			//while there is no linker - let`s be safe
			if (!t) {
				return nullptr;
			}
			//----------------------------------------
			else if (t->is_same_as(*expected_type)) {
				return c;
			}
			else if (expected_type->is_parent_of(*t)) {
				return c;
			}
			return nullptr;
		}
		template<typename T>
		void set_data(T* data, bool is_array, type_handler* new_type) {
			c.set_value(data, is_array);
			t = new_type;
		}
		void try_killing() {
			if (!(r.get_used_size() + h)) {
				delete this;
			}
		}
		//operators-----------------------------
		object& operator=(const object&) = delete;
		object& operator=(object&& obj) noexcept {
			if (this == &obj) {
				return *this;
			}
			//to do, move pointers in branches and roots
			ID = std::move(obj.ID);
			t = std::move(obj.t);
			c = std::move(obj.c);
			h = std::move(obj.h);
			return *this;
		}
	};
	struct object_handler {
		public:
			size_t				ID;		//ID
			object_handler(object* target = nullptr, size_t ID = 0) : ID(ID), target(target) {
				add_target();
			}
			object_handler(const object_handler& other_handler) : ID(other_handler.ID), target(other_handler.target) {
				add_target();
			}
			object_handler(object_handler&& other_handler) noexcept : ID(std::move(other_handler.ID)), target(std::move(other_handler.target)) {}
			~object_handler() {
				remove_target();
			}
			object_handler& operator=(const object_handler& handler) {
				if (handler.target == target) {
					return *this;
				}
				remove_target();
				target = handler.target;
				add_target();
				return *this;
			}
			object_handler& operator=(object_handler&& handler) noexcept {
				if (handler.target == target) {
					return *this;
				}
				remove_target();
				ID = std::move(handler.ID);
				target = std::move(handler.target);
				add_target();
				return *this;
			}
			void set_new_target(object* object) {
				if (object != target) {
					remove_target();
					target = object;
					add_target();
				}
			}
			operator object*() const {
				return target;
			}
			object* operator ->() const {
				return target;
			}
		private:
			object*				target;	//pointer to object
			void add_target() {
				if (target) {
					++target->h;
				}
			}
			void remove_target() {
				if (target) {
					--target->h;
					target->try_killing();
				}
			}
	};
}