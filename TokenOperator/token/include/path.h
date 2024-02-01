#pragma once
#include "object.h"
namespace dte_token {
	struct way {
		bool forward;
		size_t ID;
		constexpr bool operator==(const way& other_way) {
			return other_way.forward == forward && other_way.ID == ID;
		}
	};
	struct path {
		dynamic_array<way> ways;
		inline object* get_object(object* obj) const {
			ways.find(
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
			ways.find_ranged(
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