#pragma once
namespace tokenoperator::token::data {
	template<class V>
	struct type : object {
		public:
			using object::object;
			~type() { delete name; delete raw_name; }
			char* get_name() const { return _strdup(name); }
			char* get_raw_name() const { return _strdup(raw_name); }
			size_t get_hash() const {	return hash_code; }
		protected:
			const char* name = typeid(V).name();
			const char* raw_name = typeid(V).raw_name();
			const size_t hash_code = typeid(V).hash_code();
	};
}