#include "phase1.hpp"

namespace eToken {
	using enum_type = std::uint8_t;
	enum eToken : std::uint8_t {
		// All Phases
		invalid_,				// Invalid token. Used to indicate a syntax error.
		none_,					// No token. Used to no token is required.
		eof_,					// End of file token. Used to indicate the end of the source code.

		line_comment_,			// Comment token. eg. "''"
		block_comment_,			// Comment token. eg. "'''"
		integral_,				// Integral literal value 1234
		real_,					// real literal value 1234.5678
		string_,				// String literal value. 'hello'
		identity_,				// Identity value. eg. hello_world
		separator_,				// Separator token. eg. ','
		end_of_statement_,		//
		open_scope_,			// '('
		closed_scope_,          // ')'
		open_type_scope_,		// '<'
		closed_type_scope_,		// '>'
		open_list_scope_,		// '{'
		closed_list_scope_,		// '}'

		directive_operator_,				// # followed by a directive name #define
		dot_operator_,			// '.' operator
		auto_operator_,			// '@' operator

		operator_,				// Unknown Operator token. eg. '+'
		// Binary operators
		operator_plus_,			// '+'
		operator_minus_,		// '-'
		operator_multiply_,		// '*'
		operator_divide_,		// '/'
		operator_modulo_,		// '%'

		// Unrary operators
		operator_pre_increment_,	// '++'
		operator_pre_decrement_,	// '--'
		operator_post_increment_,	// '++'
		operator_post_decrement_,	// '--'
		operator_negative_,			// '-'
		operator_flip_,				// '~'

		// Assignment operators
		operator_assign_,			// '='
		operator_plus_assign_,		// '+='
		operator_minus_assign_,		// '-='
		operator_multiply_assign_,	// '*='
		operator_divide_assign_,	// '/='
		operator_modulo_assign_,	// '%='

		// Comparison operators
		operator_equal_,			// '=='
		operator_not_equal_,		// '!='
		operator_less_,				// '<'
		operator_greater_,			// '>'
		operator_less_equal_,		// '<='
		operator_greater_equal_,	// '>='

		// Logical operators
		operator_logical_and_,		// '&&'
		operator_logical_or_,		// '||'
		operator_logical_not_,		// '!'
		operator_logical_xor_,		// '^'
	};
};

struct Token;

struct TokenTraits {
	using p1_token_type = p1::eToken::enum_type;
	using p1_token = p1::Token;
	using p1_token_vector = p1::TokenTraits::token_vector;

	using token_enum_type = eToken::enum_type;
	using char_type = Char;
	using char_vector = std::vector<char_type>;
	using const_char_vector = std::vector<const char_type>;
	using token_vector = std::vector<Token>;



	static token_enum_type opening_independent_combine(const p1_token_vector & input
		,p1_token_vector::const_iterator it) {
		p1_token token = *it;
		auto type = token.type;
		auto lit = token.lit();
		// Only scan for non output dependent tokens. Tokens that do not require a peek at the output stack.
		switch(p1::eToken::enum_type(type)) {
			case p1::eToken::number_:
				return eToken::integral_;
			case p1::eToken::alnumus_:
				return eToken::identity_;
			case p1::eToken::symbol_:
				return eToken::operator_;
			case p1::eToken::whitespace_:
				return eToken::none_;
			case p1::eToken::newline_:
				return eToken::end_of_statement_;
			case p1::eToken::eof_:
				return eToken::eof_;
			case p1::eToken::open_paren_:
				return eToken::open_scope_;
			case p1::eToken::closed_paren_:
				return eToken::closed_scope_;
			case p1::eToken::comma_:
				return eToken::separator_;
			case p1::eToken::pound_:
				return eToken::directive_operator_;
			case p1::eToken::commercial_at_:
				return eToken::auto_operator_;
			default:
				return eToken::invalid_;
		}
	}

	static token_enum_type opening_dependent_combine(const p1_token_vector& input
		, p1_token_vector::const_iterator it
		, const token_vector& output) {

	}

	static token_enum_type opening(const p1_token_vector& input
		, p1_token_vector::const_iterator it
		, const token_vector& output) {
		if(output.empty())
			return opening_independent_combine(input, it);
		else
			return opening_dependent_combine(input, it, output);
	}


	// Given a token type curently open phase 2, returns true if this phase 1 token would close that token.
	static bool closing(p1_token_vector::const_iterator closer_it, eToken::enum_type open_type) {
		p1::Token closer_token = *closer_it;
		auto closer_type = closer_token.type;
		auto closer_lit = closer_token.lit();

		switch (open_type)
		{
		case eToken::line_comment_: // Consumes all until newline_ "''" Two single quotes.
			return closer_type == p1::eToken::newline_; break;
		case eToken::block_comment_: // Consumes all until next block_comment_ "'''" Three single quotes.
		case eToken::string_: // Consumes all until next quotation_mark_ "'"
			return closer_type == p1::eToken::quotation_mark_; break;
		case eToken::integral_: // Consumes numbers and periods and letters.
			return closer_type != p1::eToken::number_
				&& closer_type != p1::eToken::period_
				&& closer_type != p1::eToken::alnumus_; break;
		case eToken::identity_: // Consumes alnumus_
			return closer_type != p1::eToken::alnumus_; break;
		case eToken::separator_: // Consumes comma_ and whitespace_
			return closer_type != p1::eToken::comma_
				&& closer_type != p1::eToken::whitespace_; break;
		case eToken::end_of_statement_: // Consumes newline_ and whitespace_
			return closer_type != p1::eToken::newline_
				&& closer_type != p1::eToken::whitespace_; break;
		case eToken::open_scope_: // Consumes single token and whitespace_
		case eToken::closed_scope_:
		case eToken::open_type_scope_:
		case eToken::closed_type_scope_:
		case eToken::open_list_scope_:
		case eToken::closed_list_scope_:
			return closer_type != p1::eToken::whitespace_; break;
		case eToken::directive_operator_: // Consumes alnumus_
			return closer_type != p1::eToken::alnumus_; break;
		default:
			return false;
		}
	}

	// Given an open token type, source and start location: attempts to lex the token.
// Returns the token that was lexed or an invalid token if the token was not lexed.
	static Token lex(eToken::enum_type type,
		const p1_token_vector& source, 
		p1_token_vector::const_iterator it,
		const token_vector & output) {
		for (; it != source.end(); it++) {
			if (closing(it, type)) {
				return Token{ type,source.begin(),it };
			}
		}
		return Token{ eToken::invalid_,source.begin(),it };
	}
	
	//static auto begin_combine(const std::stack<Token>& source, const std::stack<Token>& output) {
//	const auto& token = source.top();
//
//	if (output.empty()) {
//		// Only scan for non output dependent tokens.
//		if (token.type == eToken::symbol_) {
//			// Check the literal of the symbol token to see if it one of the following:
//			//		2. If the literal is a '#' -> directive_literal_operator_
//			//		3. If the literal begins with a ''' -> string_literal_
//			//		4.5. if the literal begins with \\ -> comment_
//
//			if (token.lit.find(HASHTAG) != std::string::npos)
//				return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//				return TokenTraits<eToken::string_literal_>::token_type::value;
//			else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//				return TokenTraits<eToken::comment_>::token_type::value;
//			else
//				return TokenTraits<eToken::operator_>::token_type::value;
//		}
//		else if (token.type == eToken::whitespace_) {
//			return TokenTraits<eToken::whitespace_>::token_type::value;
//		}
//		else if (token.type == eToken::comma_) {
//			return TokenTraits<eToken::comma_>::token_type::value;
//		}
//		else if (token.type == eToken::open_paren_) {
//			return TokenTraits<eToken::open_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::closed_paren_) {
//			return TokenTraits<eToken::closed_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::eof_) {
//			return TokenTraits<eToken::eof_>::token_type::value;
//		}
//		else if (token.type == eToken::newline_) {
//			return TokenTraits<eToken::newline_>::token_type::value;
//		}
//		else {
//			return TokenTraits<eToken::invalid_>::token_type::value;
//		}
//	}
//	else {
//		// Scan the rest of the tokens.
//		const auto& output_token = output.top();
//
//		if (token.type == eToken::number_) {
//			// 1.1. Check if the previous token on the output stack was a float_literal_operator_.
//			//		Then we should try to combine into a float_literal_.
//			if (output_token.type == eToken::float_literal_operator_) {
//				return TokenTraits<eToken::float_literal_>::token_type::value;
//			}
//			else // 1.2. Else we should try to combine into an integer_literal_. 
//				return TokenTraits<eToken::integer_literal_>::token_type::value;
//		}
//		else if (token.type == eToken::alnumus_) {
//			// 2.1. Check if the previous token on the output stack was a directive_operator_.
//			//		Then we should try to combine into a compiler directive.
//			if (output_token.type == eToken::directive_literal_operator_) {
//				return TokenTraits<eToken::directive_>::token_type::value;
//			}
//			else // 2.2. Else we should try to combine into an Identifier.
//				return TokenTraits<eToken::identifier_>::token_type::value;
//		}
//		else if (token.type == eToken::symbol_) {
//			// Check the literal of the symbol token to see if it one of the following:
//			//		2. If the literal is a '#' -> directive_literal_operator_
//			//		3. If the literal begins with a ''' -> string_literal_
//			//		4.5. if the literal begins with \\ -> comment_
//
//			// Tokens that require a peek at the output stack.
//			//if (!output.empty()) {
//			if (token.lit.front() == '.' && output_token.type == eToken::integer_literal_)
//				return TokenTraits<eToken::float_literal_operator_>::token_type::value;
//			else if (token.lit.find(HASHTAG) != std::string::npos)
//				return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//				return TokenTraits<eToken::string_literal_>::token_type::value;
//			else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//				return TokenTraits<eToken::comment_>::token_type::value;
//			else
//				return TokenTraits<eToken::operator_>::token_type::value;
//			//}
//
//			//if (token.lit.find(HASHTAG) != std::string::npos)
//			//	return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			//else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//			//	return TokenTraits<eToken::string_literal_>::token_type::value;
//			//else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//			//	return TokenTraits<eToken::comment_>::token_type::value;
//			//else
//			//	return TokenTraits<eToken::operator_>::token_type::value;
//		}
//		else if (token.type == eToken::whitespace_) {
//			return TokenTraits<eToken::whitespace_>::token_type::value;
//		}
//		else if (token.type == eToken::newline_) {
//			return TokenTraits<eToken::newline_>::token_type::value;
//		}
//		else if (token.type == eToken::eof_) {
//			return TokenTraits<eToken::eof_>::token_type::value;
//		}
//		else if (token.type == eToken::open_paren_) {
//			return TokenTraits<eToken::open_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::closed_paren_) {
//			return TokenTraits<eToken::closed_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::comma_) {
//			return TokenTraits<eToken::comma_>::token_type::value;
//		}
//		else {
//			return TokenTraits<eToken::invalid_>::token_type::value;
//		}
//	}
//}
};

struct Token {
	eToken::enum_type type;
	TokenTraits::p1_token_vector::const_iterator begin;
	TokenTraits::p1_token_vector::const_iterator end;


};
struct LexResult {
	Token token;
	std::size_t tokens_popped;
};
static TokenTraits::token_vector combine(const TokenTraits::p1_token_vector& source) {
	TokenTraits::token_vector output;
	// While there are tokens left in the source,based on the top character of the stack determine the next type of token we should attempt to lex.
	auto cursor = source.cbegin();
	while (!source.empty()) {
		eToken::enum_type opening_token_type = TokenTraits::opening(source, cursor, output);

		// If we have a valid token type, then we should lex until we reach the end of the token.
		if (opening_token_type != eToken::invalid_) {
			LexResult lex_result = TokenTraits::lex(opening_token_type, cursor, source, output);
			if (lex_result.token.type != eToken::invalid_) {
				if (lex_result.token.type == eToken::eof_) {
					output.push_back(Token{ eToken::eof_,source.begin(),cursor });
					return output; // Lexing is complete.
				}
				else {
					output.push_back(lex_result.token);
					cursor = lex_result.token.end;
					for (auto i = 0; i < lex_result.tokens_popped; ++i)
						output.pop_back();
				}
			}
			else {
				output.push_back(lex_result.token);
				return output; // Stop lexing, error has occured.
			}
		}
		else {
			output.push_back(Token{ eToken::invalid_,source.begin(),cursor });
			return output; // Stop lexing, error has occured.
		}
	}

	// End of file, push back eof token.
	output.push_back(Token{ eToken::eof_,source.begin(),cursor });
	return output;
}

//static auto passthrough(std::stack<Token>& source, std::stack<Token>& output) {
//	Token token = source.top();
//	source.pop();
//	return token;
//}
//
//static auto begin_combine(const std::stack<Token>& source, const std::stack<Token>& output) {
//	const auto& token = source.top();
//
//	if (output.empty()) {
//		// Only scan for non output dependent tokens.
//		if (token.type == eToken::symbol_) {
//			// Check the literal of the symbol token to see if it one of the following:
//			//		2. If the literal is a '#' -> directive_literal_operator_
//			//		3. If the literal begins with a ''' -> string_literal_
//			//		4.5. if the literal begins with \\ -> comment_
//
//			if (token.lit.find(HASHTAG) != std::string::npos)
//				return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//				return TokenTraits<eToken::string_literal_>::token_type::value;
//			else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//				return TokenTraits<eToken::comment_>::token_type::value;
//			else
//				return TokenTraits<eToken::operator_>::token_type::value;
//		}
//		else if (token.type == eToken::whitespace_) {
//			return TokenTraits<eToken::whitespace_>::token_type::value;
//		}
//		else if (token.type == eToken::comma_) {
//			return TokenTraits<eToken::comma_>::token_type::value;
//		}
//		else if (token.type == eToken::open_paren_) {
//			return TokenTraits<eToken::open_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::closed_paren_) {
//			return TokenTraits<eToken::closed_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::eof_) {
//			return TokenTraits<eToken::eof_>::token_type::value;
//		}
//		else if (token.type == eToken::newline_) {
//			return TokenTraits<eToken::newline_>::token_type::value;
//		}
//		else {
//			return TokenTraits<eToken::invalid_>::token_type::value;
//		}
//	}
//	else {
//		// Scan the rest of the tokens.
//		const auto& output_token = output.top();
//
//		if (token.type == eToken::number_) {
//			// 1.1. Check if the previous token on the output stack was a float_literal_operator_.
//			//		Then we should try to combine into a float_literal_.
//			if (output_token.type == eToken::float_literal_operator_) {
//				return TokenTraits<eToken::float_literal_>::token_type::value;
//			}
//			else // 1.2. Else we should try to combine into an integer_literal_. 
//				return TokenTraits<eToken::integer_literal_>::token_type::value;
//		}
//		else if (token.type == eToken::alnumus_) {
//			// 2.1. Check if the previous token on the output stack was a directive_operator_.
//			//		Then we should try to combine into a compiler directive.
//			if (output_token.type == eToken::directive_literal_operator_) {
//				return TokenTraits<eToken::directive_>::token_type::value;
//			}
//			else // 2.2. Else we should try to combine into an Identifier.
//				return TokenTraits<eToken::identifier_>::token_type::value;
//		}
//		else if (token.type == eToken::symbol_) {
//			// Check the literal of the symbol token to see if it one of the following:
//			//		2. If the literal is a '#' -> directive_literal_operator_
//			//		3. If the literal begins with a ''' -> string_literal_
//			//		4.5. if the literal begins with \\ -> comment_
//
//			// Tokens that require a peek at the output stack.
//			//if (!output.empty()) {
//			if (token.lit.front() == '.' && output_token.type == eToken::integer_literal_)
//				return TokenTraits<eToken::float_literal_operator_>::token_type::value;
//			else if (token.lit.find(HASHTAG) != std::string::npos)
//				return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//				return TokenTraits<eToken::string_literal_>::token_type::value;
//			else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//				return TokenTraits<eToken::comment_>::token_type::value;
//			else
//				return TokenTraits<eToken::operator_>::token_type::value;
//			//}
//
//			//if (token.lit.find(HASHTAG) != std::string::npos)
//			//	return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
//			//else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
//			//	return TokenTraits<eToken::string_literal_>::token_type::value;
//			//else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
//			//	return TokenTraits<eToken::comment_>::token_type::value;
//			//else
//			//	return TokenTraits<eToken::operator_>::token_type::value;
//		}
//		else if (token.type == eToken::whitespace_) {
//			return TokenTraits<eToken::whitespace_>::token_type::value;
//		}
//		else if (token.type == eToken::newline_) {
//			return TokenTraits<eToken::newline_>::token_type::value;
//		}
//		else if (token.type == eToken::eof_) {
//			return TokenTraits<eToken::eof_>::token_type::value;
//		}
//		else if (token.type == eToken::open_paren_) {
//			return TokenTraits<eToken::open_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::closed_paren_) {
//			return TokenTraits<eToken::closed_paren_>::token_type::value;
//		}
//		else if (token.type == eToken::comma_) {
//			return TokenTraits<eToken::comma_>::token_type::value;
//		}
//		else {
//			return TokenTraits<eToken::invalid_>::token_type::value;
//		}
//	}
//}
//
//static constexpr auto do_combine(eToken token, const std::string& literal, std::stack<Token>& source, std::stack<Token>& output) {
//	switch (token) {
//		// Phase 1 Tokens which will pass-through to the output stack.
//	case eToken::whitespace_: return passthrough(source, output);
//	case eToken::newline_: return passthrough(source, output);
//	case eToken::open_paren_: return passthrough(source, output);
//	case eToken::closed_paren_: return passthrough(source, output);
//	case eToken::comma_: return passthrough(source, output);
//	case eToken::eof_: return passthrough(source, output);
//
//		// Phase 2 Tokens
//	case eToken::comment_: return TokenTraits<eToken::comment_>::perform_combine(source, output);
//	case eToken::operator_: return TokenTraits<eToken::operator_>::perform_combine(source, output);
//	case eToken::directive_literal_operator_: return TokenTraits<eToken::directive_literal_operator_>::perform_combine(source, output);
//	case eToken::identifier_: return TokenTraits<eToken::identifier_>::perform_combine(source, output);
//	case eToken::integer_literal_: return TokenTraits<eToken::integer_literal_>::perform_combine(source, output);
//	case eToken::float_literal_: return TokenTraits<eToken::float_literal_>::perform_combine(source, output);
//	case eToken::float_literal_operator_: return TokenTraits<eToken::float_literal_operator_>::perform_combine(source, output);
//		//case eToken::string_literal_: return TokenTraits<eToken::string_literal_>::perform_combine(source, output);
//		//case eToken::directive_: return TokenTraits<eToken::directive_>::perform_combine(source, output);
//		//case eToken::operator_: return TokenTraits<eToken::operator_>::perform_combine(source, output);
//		//case eToken::start_scope_: return TokenTraits<eToken::start_scope_>::perform_combine(source, output);
//		//case eToken::end_scope_: return TokenTraits<eToken::end_scope_>::perform_combine(source, output);
//		//case eToken::separator_: return TokenTraits<eToken::separator_>::perform_combine(source, output);
//		//case eToken::identifier_: return TokenTraits<eToken::identifier_>::perform_combine(source, output);
//		//case eToken::comment_: return TokenTraits<eToken::comment_>::perform_combine(source, output);
//		//case eToken::float_literal_operator_: return TokenTraits<eToken::float_literal_operator_>::perform_combine(source, output);
//		//case eToken::directive_literal_operator_: return TokenTraits<eToken::directive_literal_operator_>::perform_combine(source, output);
//
//	default:
//		if (token != eToken::invalid_) {
//			std::cout << "[WARNING] TokenTraits<eToken::invalid_>::perform_combine : Unimplemented token type attempted to do_combine: " << token_to_string(token) << "\n\n";
//		}
//		return Token{ eToken::invalid_,"" };
//	}
//}

	//// Conditions for building the token.
	//auto association() const -> int;		// Left or right, or none.
	//auto precidence() const -> int;			// Higher precidence means we will evaluate it last.
	//auto terminator() const -> bool;		// The token that will terminate consumption of characters for this token's literal.
	//auto consumption() const -> bool;		// The type of consumption this token uses. unary, binary, variadic right, variadic left or none.
	//auto is(std::string_view) const -> bool;  // true if the required literal is equal to the given string.

	//// Result of building the token.
	//auto popped() const -> bool;					// Characters popped from the output stack.
	//auto advanced() const -> bool;					// Characters advanced in the input stack.
	//auto literal() const->std::string_view;		// The literal that was created
	//auto identity() const->std::string_view;		// The identity(hash) of the token. equal for all tokens of the same type and value.
	//auto type() const->eToken::eToken;			// The type of this token.

	//auto lex(std::stack<char>& input, std::stack<char>& output) -> Token;



static auto combine_tokens(std::stack<Token> source) {
	std::stack<Token> output;
	while (!source.empty()) {
		const Token initial_token = source.top();
		auto try_combine = begin_combine(source, output);
		// If we have a valid token type, then we should lex until we reach the end of the token.
		if (try_combine != eToken::invalid_) {
			auto result_token = do_combine(try_combine, initial_token.lit, source, output);
			// If the result of the combination is a valid token, then we should push it to the output stack.
			if (result_token.type != eToken::invalid_) {
				// if the token is a none_ token, then we should not push anything to the output stack.
				if (result_token.type != eToken::empty_) {
					output.push(result_token);
				}
			}
			// Else we have a user syntax error or not implemented token, the tokens surrounding the token we attempted were not what we expected.
			else
				throw std::runtime_error("Syntax error during token construction. Attempting to combine: " + token_to_string(try_combine) + " but got " + token_to_string(result_token.type) + " literal: " + result_token.lit + "\n");
		}
		// Else we have a token that is not a part of the Candi language syntax in the source code.
		else {
			std::string error = "Invalid character at start of token. Offending token: " + token_to_string(initial_token.type);
			throw std::runtime_error(error);
		}
	}
	return meta::reverse_stack(output);
} // end combine_tokens
