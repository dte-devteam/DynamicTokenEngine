#pragma once
#define SINGLETON(THIS)						\
	static THIS& get_instance() {			\
		static THIS instance;				\
		return instance;					\
	}										\
	THIS(THIS const&) = delete;				\
	void operator=(THIS const&) = delete;