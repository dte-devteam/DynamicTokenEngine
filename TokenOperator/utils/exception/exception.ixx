export module exception;
export namespace dte_utils {
	struct exception {
		protected:
			size_t _error_code;
			const char* _what;
		public:
			exception(size_t error_code = 0) noexcept : _error_code(error_code), _what(nullptr) {}
			template<size_t N>
			exception(size_t error_code, const char(&message)[N]) noexcept : _error_code(error_code), _what(message) {}
			exception(const exception& ex) noexcept : _error_code(ex._error_code), _what(ex._what) {}
			exception& operator=(const exception& ex) noexcept {
				if (this == &ex) {
					return *this;
				}
				_error_code = ex._error_code;
				_what = ex._what;
				return *this;
			}
			virtual ~exception() {}
			const char* what() const {
				return _what ? _what : "Unknown error";
			}
			size_t error_code() const {
				return _error_code;
			}
	};
}