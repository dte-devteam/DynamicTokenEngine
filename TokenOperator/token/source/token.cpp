#include "../include/token.h"
using namespace dte_utils;
namespace dte_token {
	dynamic_wstring& token::link::getcallname() {
		return pseudonym.get_used_size() ? pseudonym : pointer->name;
	}
	const dynamic_wstring& token::link::getcallname() const {
		return pseudonym.get_used_size() ? pseudonym : pointer->name;
	}
	token::link* token::get_token(const dynamic_wstring& token_name) const {
		return links.find(
			[&token_name](const link& iter) noexcept {
				return iter.getcallname() == token_name;
			}
		);
	}
	token::link* token::get_token(dynamic_wstring&& token_name) const {
		return links.find(
			[&token_name](const link& iter) noexcept {
				return iter.getcallname() == token_name;
			}
		);
	}
	token::link* token::get_token(const dynamic_path& token_path, size_t shift) const {
		link* l = get_token(token_path[shift]);
		return ++shift < token_path.get_used_size() && l ? get_token(token_path, shift) : l;
	}
	token::link* token::get_token(dynamic_path&& token_path, size_t shift) const {
		link* l = get_token(token_path[shift]);
		return ++shift < token_path.get_used_size() && l ? get_token(token_path, shift) : l;
	}
	void token::copy_links(const token& source) {
		links += source.links;
	}
}