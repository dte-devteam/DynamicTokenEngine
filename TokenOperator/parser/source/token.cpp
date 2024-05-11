#include "../include/token.h"
using namespace dte_utils;
using namespace dte_token;
using namespace dte_parser;
dynamic_wstring& token::link::getcallname() {
	return pseudonym.get_used_size() ? pseudonym : pointer->name;
}
const dynamic_wstring& token::link::getcallname() const {
	return pseudonym.get_used_size() ? pseudonym : pointer->name;
}