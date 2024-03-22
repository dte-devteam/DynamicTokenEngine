#pragma once
#include "object.h"
namespace dte_token {
	struct way {
		bool forward;
		size_t ID;
		bool operator==(const way& other_way) {
			return other_way.forward == forward && other_way.ID == ID;
		}
	};
	struct path : dte_utils::dynamic_array<way> {
		inline object* get_object(object* obj) const {
			find(
				[&obj](const way& w) {
					if (obj) {
						obj = obj->get_object(w.ID, w.forward);
						return false;
					}
					else {
						return true;
					}
				}
			);
			return obj;
		}
		inline object* get_object(object* obj, size_t from, size_t to) const {
			find_ranged(
				[&obj](const way& w) {
					if (obj) {
						obj = obj->get_object(w.ID, w.forward);
						return false;
					}
					else {
						return true;
					}
				},
				from, 
				to
			);
			return obj;
		}
	};
}