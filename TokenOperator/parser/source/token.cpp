#include "../include/token.h"
using namespace dte_utils;
using namespace dte_parser;
token::link::~link() {
	delete token_relation;
}
token::~token() {
	delete meta;
}