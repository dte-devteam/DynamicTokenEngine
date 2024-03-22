#pragma once
namespace dte_token {
	#define SINGLE_DELETER(T)	[](void* x) { delete	static_cast<T*>(x); }
	#define MULTIPLE_DELETER(T)	[](void* x) { delete[]	static_cast<T*>(x); }
	typedef void (*deleter)(void*);
	struct container {
		//c style allocation can be UB
		/*
		* can`t be copied
		* because destructor will release memory and resourses of copy pointer
		*/
		public:
			container() : container((char*)nullptr, 0) {}
			template<typename T>
			container(T* source, bool is_array){
				data = source;
				destructor = is_array ? MULTIPLE_DELETER(T) : SINGLE_DELETER(T);
			}
			container(const container&) = delete;
			container(container&& cont) noexcept : data(std::move(cont.data)), destructor(std::move(cont.destructor)) {}
			~container() {
				destructor(data);
			}
			template<typename T>
			void set_value(T* source, bool is_array) {
				destructor(data);
				data = source;
				destructor = is_array ? MULTIPLE_DELETER(T) : SINGLE_DELETER(T);
			}
			void unbind() {
				data = nullptr;
			}
			void* get_data() const {
				return data;
			}
			//operators-----------------------------
			container& operator =(const container&) = delete;
			container& operator =(container&& cont) {
				if (this == &cont) {
					return *this;
				}
				destructor(data);
				data = std::move(cont.data);
				destructor = std::move(cont.destructor);
				return *this;
			}
			operator void*() const {
				return data;
			}
			//--------------------------------------
		protected:
			void*	data;
			deleter	destructor;
	};
}