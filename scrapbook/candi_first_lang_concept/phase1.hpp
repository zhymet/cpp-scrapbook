#include <vector>
#include <stack>
#include "constants.hpp"

namespace p1 {
	namespace eToken {
		using enum_type = unsigned;
		enum eToken : unsigned {
			// All Phases
			invalid_,				// Invalid token. Used to indicate a syntax error.
			// Phase 1 - Lexing (Tokenization)
			number_,				// Number literal value. Unchecked for overflow.
			alnumus_,				// Alphanumeric value with underscores. eg. "hello_world"
			symbol_,				// Extended symbol value. eg. "÷"
			whitespace_,			// Whitespace token ' '
			newline_,				// Newline token '\n'
			eof_,					// End of file token. '\0'
			open_paren_,			// '('
			closed_paren_,          // ')'
			comma_,					// ','
			period_,				// '.'
			pound_,					// '#'
			commercial_at_,			// '@'
			exclamation_mark_,		// '!'
			question_mark_,			// '?'
			quotation_mark_,		// '"'
			apostrophe_,			// '''
			colon_,					// ':'
			semicolon_,				// ';'
			ampersand_,				// '&'
			percent_sign_,			// '%'
			asterisk_,				// '*'
			plus_sign_,				// '+'
			minus_sign_,			// '-'
			solidus_,				// '/'
			reverse_solidus_,		// '\'
			equals_sign_,			// '='
			less_than_sign_,		// '<'
			greater_than_sign_,		// '>'
			circumflex_accent_,		// '^'
			low_line_,				// '_'
			vertical_line_,			// '|'
			tilde_,					// '~'
			left_curly_bracket_,	// '{'
			right_curly_bracket_,	// '}'
			left_square_bracket_,	// '['
			right_square_bracket_,	// ']'
			left_apostrophe_		// '`'
		};
	};

	struct Token;

	struct TokenTraits {
		using token_type = eToken::enum_type;
		using char_type = Char;
		using char_vector = std::vector<char_type>;
		using const_char_vector = std::vector<const char_type>;
		using token_vector = std::vector<Token>;

		// Returns the type of token the passed character would open.
		static constexpr eToken::enum_type opening(const_char_vector::const_iterator it) {
			auto c = *it;
			if (c.is_numeric()) {
				return eToken::number_;
			}
			else if (c.is_alpha()) {
				return eToken::alnumus_;
			}
			else if (c.is_whitespace()) {
				return eToken::whitespace_;
			}
			else if (c.is_newline()) {
				return eToken::newline_;
			}
			else if (c.val == '\0') {
				return eToken::eof_;
			}
			else if (c.val == '@') {
				return eToken::commercial_at_;
			}
			else if (c.is_symbol()) {
				if (c.is_core_symbol()) {
					if (c.val == '(') {
						return eToken::open_paren_;
					}
					else if (c.val == ')') {
						return eToken::closed_paren_;
					}
					else if (c.val == ',') {
						return eToken::comma_;
					}
					else if (c.val == '.') {
						return eToken::period_;
					}
					else if (c.val == '#') {
						return eToken::pound_;
					}
					else if (c.val == '@') {
						return eToken::commercial_at_;
					}
					else if (c.val == '!') {
						return eToken::exclamation_mark_;
					}
					else if (c.val == '?') {
						return eToken::question_mark_;
					}
					else if (c.val == '"') {
						return eToken::quotation_mark_;
					}
					else if (c.val == '\'') {
						return eToken::apostrophe_;
					}
					else if (c.val == ':') {
						return eToken::colon_;
					}
					else if (c.val == ';') {
						return eToken::semicolon_;
					}
					else if (c.val == '&') {
						return eToken::ampersand_;
					}
					else if (c.val == '%') {
						return eToken::percent_sign_;
					}
					else if (c.val == '*') {
						return eToken::asterisk_;
					}
					else if (c.val == '+') {
						return eToken::plus_sign_;
					}
					else if (c.val == '-') {
						return eToken::minus_sign_;
					}
					else if (c.val == '/') {
						return eToken::solidus_;
					}
					else if (c.val == '\\') {
						return eToken::reverse_solidus_;
					}
					else if (c.val == '=') {
						return eToken::equals_sign_;
					}
					else if (c.val == '<') {
						return eToken::less_than_sign_;
					}
					else if (c.val == '>') {
						return eToken::greater_than_sign_;
					}
					else if (c.val == '^') {
						return eToken::circumflex_accent_;
					}
					else if (c.val == '_') {
						return eToken::low_line_;
					}
					else if (c.val == '|') {
						return eToken::vertical_line_;
					}
					else if (c.val == '~') {
						return eToken::tilde_;
					}
					else if (c.val == '{') {
						return eToken::left_curly_bracket_;
					}
					else if (c.val == '}') {
						return eToken::right_curly_bracket_;
					}
					else if (c.val == '[') {
						return eToken::left_square_bracket_;
					}
					else if (c.val == ']') {
						return eToken::right_square_bracket_;
					}
					else if (c.val == '?') {
						return eToken::question_mark_;
					}
					else if (c.val == '`') {
						return eToken::left_apostrophe_;
					}
					else {
						return eToken::symbol_;
					}
				}
				else if (c.is_extended_symbol()) {
					return eToken::symbol_;
				}
			}
			else {
				return eToken::invalid_;
			}
		}

		// Given a token type curently open, returns true if this character would close that token.
		static constexpr bool closing(const_char_vector::const_iterator it, eToken::enum_type type) {
			auto c = *it;
			switch (type)
			{
			case eToken::number_:
				return !c.is_numeric();
			case eToken::alnumus_:
				return !c.is_alnumus();
			case eToken::whitespace_:
				return !c.is_whitespace();
			case eToken::newline_:
				return !c.is_newline();
				// Single character tokens
			case eToken::eof_:
			case eToken::open_paren_:
			case eToken::closed_paren_:
			case eToken::comma_:
			case eToken::period_:
			case eToken::pound_:
			case eToken::commercial_at_:
			case eToken::exclamation_mark_:
			case eToken::question_mark_:
			case eToken::quotation_mark_:
			case eToken::apostrophe_:
			case eToken::colon_:
			case eToken::semicolon_:
			case eToken::ampersand_:
			case eToken::percent_sign_:
			case eToken::asterisk_:
			case eToken::plus_sign_:
			case eToken::minus_sign_:
			case eToken::solidus_:
			case eToken::reverse_solidus_:
			case eToken::equals_sign_:
			case eToken::less_than_sign_:
			case eToken::greater_than_sign_:
			case eToken::circumflex_accent_:
			case eToken::low_line_:
			case eToken::vertical_line_:
			case eToken::tilde_:
			case eToken::left_curly_bracket_:
			case eToken::right_curly_bracket_:
			case eToken::left_square_bracket_:
			case eToken::right_square_bracket_:
			case eToken::left_apostrophe_:
				return false;
			default:
				return false;
			}
		}

		// Given an open token type, source and start location: attempts to lex the token.
		// Returns the token that was lexed or an invalid token if the token was not lexed.
		static Token lex(eToken::enum_type type, const const_char_vector& source, const_char_vector::const_iterator it) {
			for (; it != source.end(); it++) {
				if (closing(it, type)) {
					return Token{ type,source.begin(),it };
				}
			}
			return Token{ eToken::invalid_,source.begin(),it };
		}

		// Given a source code vector of const characters, tokenizes the source into a vector of tokens.
		static token_vector tokenize(const TokenTraits::const_char_vector& source) {
			token_vector output;
			// While there are tokens left in the source,based on the top character of the stack determine the next type of token we should attempt to lex.
			auto cursor = source.cbegin();
			if (!source.empty()) {
				while (cursor != source.end()) {
					auto opening_token_type = TokenTraits::opening(cursor);

					// If we have a valid token type, then we should lex until we reach the end of the token.
					if (opening_token_type != eToken::invalid_) {
						auto result_token = TokenTraits::lex(opening_token_type, source, cursor);
						if (result_token.type != eToken::invalid_) {
							output.push_back(result_token);
							cursor = result_token.end;
						}
						else {
							output.push_back(result_token);
							return output; // Stop lexing, invalid token syntax.
						}
					}
					else {
						output.push_back(Token{ eToken::invalid_,source.begin(),cursor });
						return output; // Stop lexing, invalid character in source.
					}
				}
			}
			else {
				output.push_back(Token{ eToken::invalid_,source.begin(),cursor });
				return output; // Stop lexing, empty source.
			}
			// End of file, push back eof token. Finish Lex.
			output.push_back(Token{ eToken::eof_,source.begin(),cursor });
			return output;
		}

		// Given a vector of tokens as a result of tokenize(), ensures there are no invalid tokens at the end of the source.
		// (Invalid at end of source indicates an error in tokenization) 
		// Data from invalid back token may be used to report errors.
		static bool validate(const token_vector& tokenized_source) {
			// If there is an invalid token at the end of the source, then the source is invalid.
			if (tokenized_source.back().type == eToken::invalid_) {
				return false;
			}
			// If the end of the source is not an eof token, then the source is invalid.
			if (tokenized_source.back().type != eToken::eof_) {
				return false;
			}
			return true;
		}
	};

	struct Token {
		const eToken::enum_type type;
		const TokenTraits::const_char_vector::const_iterator begin;
		const TokenTraits::const_char_vector::const_iterator end;

		Token(eToken::enum_type type, TokenTraits::const_char_vector::const_iterator begin, TokenTraits::const_char_vector::const_iterator end)
			: type(type), begin(begin), end(end) {
		}
		std::string_view lit() const {
			std::string s;
			for (auto it = begin; it != end; it++) {
				s += it->val;
			}
			return std::string_view(s);
		}
	};

	struct TokenizedSource {
		const TokenTraits::const_char_vector& source;
		const std::vector<Token> tokens;
		const bool is_valid;

		TokenizedSource(const TokenTraits::const_char_vector& source)
			: source(source), tokens(TokenTraits::tokenize(source)), is_valid(TokenTraits::validate(tokens)) {
		}
	};
}
