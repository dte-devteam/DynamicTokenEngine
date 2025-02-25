#pragma once
#include "ref.h"
namespace dte_utils {
	template<typename T>
	struct unique_ref {
		protected:
			ref_pointer<T> instance;
		public:
			unique_ref(ref_pointer<T> instance = nullptr) : instance(instance) {}
			unique_ref(const unique_ref&) = delete;
			unique_ref(unique_ref&& r) {
				std::swap(instance, r.instance);
			}
			~unique_ref() {
				if constexpr (std::is_array_v<T>) {
					delete[] instance;
				}
				else if constexpr (!return_type_v<T>) {
					delete instance;
				}
			}
			unique_ref& operator=(const unique_ref&) = delete;
			unique_ref& operator=(unique_ref&& r) noexcept {
				if (this == &r) {
					return *this;
				}
				std::swap(instance, r.instance);
				return *this;
			}
			template<typename R = return_type_t<T>, typename ...Args>
			R operator()(Args&&... args) const {
				return instance(std::forward<Args>(args)...);
			}
			template<typename U = std::enable_if_t<ref_instantiable<T>, T>>
			U& operator*() const {
				return *instance;
			}
			template<typename U = std::enable_if_t<ref_instantiable<T>, T>>
			U* operator->() const {
				return instance;
			}
			template<typename U = std::enable_if_t<std::is_array_v<T>, decltype(std::declval<T>()[0])>>
			U& operator[](size_t index) const {
				return instance[index];
			}
	};
}