#include "pch.h"
#include "meta.hpp"
#include <bitset>
#include <array>
#include <stdio.h>
#include <chrono>
#include <stack>
#include <any>
#include <variant>
#include <algorithm>
#include <list>
// Template Meta Utilities

namespace meta {
	// Reverse a range iterator
	template<typename It>
	class Range
	{
		It b, e;
	public:
		Range(It b, It e) : b(b), e(e) {}
		It begin() const { return b; }
		It end() const { return e; }
	};

	template<typename ORange, typename OIt = decltype(std::begin(std::declval<ORange>())), typename It = std::reverse_iterator<OIt>>
	Range<It> reverse(ORange&& originalRange) {
		return Range<It>(It(std::end(originalRange)), It(std::begin(originalRange)));
	}

	template<typename T>
	constexpr auto one_of(T c, std::initializer_list<T> list) {
		for (auto elem : list)
		{
			if (elem == c)
				return true;
		}
		return false;
	}

	// Convert a string_view into a stack of characters.
	static auto sv_to_stack(std::string_view source) {
		std::stack<char> output;
		for (auto& c : meta::reverse(source)) {
			output.push(c);
		}
		return output;
	}

	// Convert array of string views into one string view.
	template<std::size_t N>
	static auto svarray_to_string(std::array<std::string_view, N> source) {
		std::string output;
		for (auto& sv : source) {
			output += sv;
			output += '\n';
		}
		return output;
	}

	// Reverse a stack
	template<typename T>
	static auto reverse_stack(std::stack<T> source) {
		std::stack<T> output;
		std::vector<T> temp;
		temp.reserve(source.size());
		while (!source.empty()) {
			temp.push_back(source.top());
			source.pop();
		}
		
		for (auto& elem : temp) {
			output.push(std::move(elem));
		}

		return output;
	}


	inline constexpr std::string string_from_char(char x)
	{
		// https://www.geeksforgeeks.org/how-to-convert-a-single-character-to-string-in-cpp/
		// string class has a constructor
		// that allows us to specify size of
		// string as first parameter and character
		// to be filled in given size as second
		// parameter.
		std::string s(1, x);

		return s;
	}
}

#define CANDIL_KERNEL
#ifdef CANDIL_KERNEL
// User-defined literal for string_view
constexpr std::string_view operator""_line(const char* str, std::size_t size) {
	return std::string_view(str, size);
}

constexpr auto candil_source_code = std::to_array<std::string_view>({
#include "hundred_doors.candil"
#include <list>
	});

consteval auto get_candil_source_code() {
	return candil_source_code;
}

#define CANDIL_SOURCE get_candil_source_code()
#endif

namespace candi {

	class TokenCombineCriticalProgrammerLogicError : public std::runtime_error {
	public:
		TokenCombineCriticalProgrammerLogicError(const char* msg) : std::runtime_error(msg) {}
	};

	class TokenCombineUserSyntaxError : public std::runtime_error {
	public:
		TokenCombineUserSyntaxError(const char* msg) : std::runtime_error(msg) {}
	};

	class TokenCombineUserDirectiveKeywordSyntaxError : public std::runtime_error {
	private:
	public:
		TokenCombineUserDirectiveKeywordSyntaxError(std::string invalid_keyword_literal) : std::runtime_error(
			std::string("[TokenCombineUserDirectiveKeywordSyntaxError]  Invalid keyword ["
				+invalid_keyword_literal + "] in literal of top() Token on source stack.").c_str()
		) {}
	};

	class ParseAstUserSyntaxError : public std::runtime_error {
	public:
		ParseAstUserSyntaxError(const char* msg) : std::runtime_error(msg) {}
	};

	constexpr auto NUMERIC_CHARACTERS = {
		'0','1','2','3','4','5','6','7','8','9'
	};

	constexpr auto ALPHABETIC_CHARACTERS = {
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};

	constexpr auto ALNUMUS_CHARACTERS = {
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'_','0','1','2','3','4','5','6','7','8','9'
	};

	// Note : The open and closed parenthesis are not included in the symbol characters.
	// Note : The comma is not included in the symbol characters.
	constexpr auto SYMBOL_CHARACTERS_NO_UNDERSCORE = {
		'!','@','#','$','%','^','&','*','-','+','=','{','}','[',']','|','\\',';',':','\'','\"','<','>','?','/','~','`','.'
	};

	// Note : The open and closed parenthesis are not included in the symbol characters.
	// Note : The comma is not included in the symbol characters.
	constexpr auto SYMBOL_CHARACTERS = {
		'_','!','@','#','$','%','^','&','*','-','+','=','{','}','[',']','|','\\',';',':','\'','\"','<','>','?','/','~','`','.'
	};

	constexpr auto COMMA = ',';
	constexpr auto OPEN_PARENTHESIS = '(';
	constexpr auto CLOSED_PARENTHESIS = ')';
	constexpr auto WHITESPACE = ' ';
	constexpr auto NEWLINE = '\n';
	constexpr auto ENDFILE = '\0';
	constexpr auto TABSPACE = '\t';
	constexpr auto HASHTAG = '#';
	constexpr auto PERIOD = '.';
	constexpr auto SINGLE_QUOTE = '\'';
	constexpr auto TRIPLE_QUOTE = "\'\'\'";
	constexpr auto OPEN_ANGLE_BRACKET = '<';
	constexpr auto CLOSED_ANGLE_BRACKET = '>';
	constexpr auto DOUBLE_FORWARD_SLASH = "//";


	auto CANDIL_KEYWORD_ENTER = "enter";
	auto CANDIL_KEYWORD_START = "start";
	auto CANDIL_KEYWORD_DEFINE = "define";
	auto CANDIL_KEYWORD_METHOD = "method";
	auto CANDIL_KEYWORD_CALL = "call";
	auto CANDIL_KEYWORD_TYPE = "type";
	auto CANDIL_KEYWORD_IF = "if";
	auto CANDIL_KEYWORD_ELSE = "else";
	auto CANDIL_KEYWORD_ELIF = "elif";
	auto CANDIL_KEYWORD_WHILE = "while";
	auto CANDIL_KEYWORD_FOR = "for";
	auto CANDIL_KEYWORD_FORIF = "forif";
	auto CANDIL_KEYWORD_BREAK = "break";
	auto CANDIL_KEYWORD_CONTINUE = "continue";
	auto CANDIL_KEYWORD_RETURN = "return";
	auto CANDIL_KEYWORD_INTO = "into";

	auto CANDIL_KEYWORD_PRINT = "print";


	constexpr auto CANDIL_KEYWORD_KEYWORDS = {
		// Directives
		"enter",
		"start",
		"define",
		"method",
		"call",
		"type",

		// Control flow
		"if",
		"else",
		"elif",
		"while",
		"for",
		"forif",
		"break",
		"continue",
		"return",
		"into",

		// Special Methods
		"print"
	};


	enum class eToken {
		// All Phases
		invalid_,				// Invalid token. Used to indicate a syntax error.
		// Phase 1 - Lexing (Tokenization)
		number_,				// Number literal value. Unchecked for overflow.
		alnumus_,				// Alphanumeric value with underscores. eg. "hello_world"
		symbol_,				// Symbol value. eg. "++"
		whitespace_,			// Whitespace token ' '
		newline_,				// Newline token '\n'
		eof_,					// End of file token. '\0'
		open_paren_,			// '('
		closed_paren_,          // ')'
		comma_,					// ','

		// Phase 2 - Combination (Token Literation)
		directive_,             // '#' converts the following alnumus token into a compiler directive.		
		integer_literal_,	    // Integer literal value. cpp_type = unsigned long long.
		float_literal_,         // Floating point literal value. cpp_type = float.
		string_literal_,        // String literal value. cpp_type = std::string.
		operator_,              // Any symbol that is not a number, alnumus, whitespace, newline, or eof, directive, scope start or scope end.
		//		Note: A symbol can be a combination of symbols. eg. "+=". Symbols characters may not be seperated by whitespace.
		start_scope_,	        // '('
		end_scope_,		        // ')' 
		separator_,              // ',' used to seperate arguments.
		identifier_,            // Any alnumus that is not a special word.
		comment_,               // '//' converts all the following tokens until a newline into a comment.

		float_literal_operator_,// '.' between two numbers.
		directive_literal_operator_	,	// '#' before an alnumus token.

		// Phase 3 - Sanitization (Token Validation & Removal of Redundant Tokens)
		eos_,					// End of statement token. Indicates the end of a statement.

		// All Phases
		empty_					// Empty token. Used to indicate no token is to be pushed onto the output stack.
	};

	std::string token_to_string(eToken token) {
		switch (token) {
		case eToken::empty_: return "empty";
			//Phase 1
		case eToken::invalid_: return "invalid";
		case eToken::number_: return "number";
		case eToken::alnumus_: return "alnumus";
		case eToken::symbol_: return "symbol";
		case eToken::whitespace_: return "whitespace";
		case eToken::newline_: return "newline";
		case eToken::eof_: return "eof";
		case eToken::open_paren_: return "open_paren";
		case eToken::closed_paren_: return "closed_paren";
		case eToken::comma_: return "comma";


			//Phase 2
		case eToken::integer_literal_: return "integer_literal";
		case eToken::float_literal_: return "float_literal";
		case eToken::string_literal_: return "string_literal";
		case eToken::directive_: return "directive";
		case eToken::operator_: return "operator";
		case eToken::start_scope_: return "start_scope";
		case eToken::end_scope_: return "end_scope";
		case eToken::separator_: return "separator";
		case eToken::comment_: return "comment";
		case eToken::identifier_: return "identifier";

		case eToken::float_literal_operator_: return "float_literal_operator";
		case eToken::directive_literal_operator_: return "directive_literal_operator";

		//Phase 3
			case eToken::eos_: return "eos";

		default: return "unknown";
		}
	}

	struct Token {
		eToken type;
		std::string lit;
	};

#define DEFINE_PERFORM_LEX\
	static Token perform_lex(std::stack<char>& source, std::stack<Token>& output) { \
		std::string literal;\
		while (!source.empty() && !closing(source.top())) {\
			literal += source.top();\
			source.pop();\
		}\
		return Token{ token_type_v,literal };\
	}

#define START_TOKEN_TRAITS(type)\
	template<> struct TokenTraits<eToken::type> : public TokenTraitsBase {\
		using token_type = std::integral_constant<eToken, eToken::type>;\
		static constexpr token_type::value_type token_type_v = token_type::value;

#define END_TOKEN_TRAITS\
	static Token perform_lex(std::stack<char>& source, std::stack<Token>& output) { \
		std::string literal;\
		while (!source.empty() && !closing(source.top())) {\
			literal += source.top();\
			source.pop();\
		}\
		return Token{ token_type_v,literal };\
	}\
}

	// Base Class Token
	struct TokenTraitsBase {
		using string_type = std::string;
		using size_type = std::size_t;
		using token_enum = eToken;

		static constexpr bool opening(char c) {
			return false;
		}
		static constexpr bool closing(char c) {
			return false;
		}

	};

	template<eToken type>
	struct TokenTraits : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, type>;
		static constexpr token_type::value_type token_type_v = token_type::value;
	};


	START_TOKEN_TRAITS(invalid_)
		static constexpr bool opening(char c) {
		return false;
	}
	static constexpr bool closing(char c) {
		return false;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(number_)
		static constexpr bool opening(char c) {
		return meta::one_of(c, NUMERIC_CHARACTERS);
	}
	static constexpr bool closing(char c) {
		return !meta::one_of(c, NUMERIC_CHARACTERS);
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(alnumus_)
		static constexpr bool opening(char c) {
		return meta::one_of(c, ALPHABETIC_CHARACTERS);
	}
	static constexpr bool closing(char c) {
		return !meta::one_of(c, ALNUMUS_CHARACTERS);
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(symbol_)
		static constexpr bool opening(char c) {
		return meta::one_of(c, SYMBOL_CHARACTERS);
	}
	static constexpr bool closing(char c) {
		return !meta::one_of(c, SYMBOL_CHARACTERS);
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(whitespace_)
		static constexpr bool opening(char c) {
		return c == WHITESPACE || c == TABSPACE;
	}
	static constexpr bool closing(char c) {
		return c != WHITESPACE && c != TABSPACE;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(newline_)
		static constexpr bool opening(char c) {
		return c == NEWLINE;
	}
	static constexpr bool closing(char c) {
		return c != NEWLINE;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(eof_)
		static constexpr bool opening(char c) {
		return c == ENDFILE;
	}
	static constexpr bool closing(char c) {
		return c != ENDFILE;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(open_paren_)
		static constexpr bool opening(char c) {
		return c == OPEN_PARENTHESIS;
	}
	static constexpr bool closing(char c) {
		return c != OPEN_PARENTHESIS;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(closed_paren_)
		static constexpr bool opening(char c) {
		return c == CLOSED_PARENTHESIS;
	}
	static constexpr bool closing(char c) {
		return c != CLOSED_PARENTHESIS;
	}
	END_TOKEN_TRAITS;

	START_TOKEN_TRAITS(comma_)
		static constexpr bool opening(char c) {
		return c == COMMA;
	}
	static constexpr bool closing(char c) {
		return c != COMMA;
	}
	END_TOKEN_TRAITS;

	static constexpr auto begin_lex(char c) {
		if (TokenTraits<eToken::number_>::opening(c)) {
			return TokenTraits<eToken::number_>::token_type::value;
		}
		else if (TokenTraits<eToken::alnumus_>::opening(c)) {
			return TokenTraits<eToken::alnumus_>::token_type::value;
		}
		else if (TokenTraits<eToken::symbol_>::opening(c)) {
			return TokenTraits<eToken::symbol_>::token_type::value;
		}
		else if (TokenTraits<eToken::whitespace_>::opening(c)) {
			return TokenTraits<eToken::whitespace_>::token_type::value;
		}
		else if (TokenTraits<eToken::newline_>::opening(c)) {
			return TokenTraits<eToken::newline_>::token_type::value;
		}
		else if (TokenTraits<eToken::eof_>::opening(c)) {
			return TokenTraits<eToken::eof_>::token_type::value;
		}
		else if (TokenTraits<eToken::open_paren_>::opening(c)) {
			return TokenTraits<eToken::open_paren_>::token_type::value;
		}
		else if (TokenTraits<eToken::closed_paren_>::opening(c)) {
			return TokenTraits<eToken::closed_paren_>::token_type::value;
		}
		else if (TokenTraits<eToken::comma_>::opening(c)) {
			return TokenTraits<eToken::comma_>::token_type::value;
		}
		else {
			return TokenTraits<eToken::invalid_>::token_type::value;
		}
	}

	static constexpr auto do_lex(eToken type, std::stack<char>& source, std::stack<Token>& output) {
		switch (type) {
		case eToken::number_: return TokenTraits<eToken::number_>::perform_lex(source, output);
		case eToken::alnumus_: return TokenTraits<eToken::alnumus_>::perform_lex(source, output);
		case eToken::symbol_: return TokenTraits<eToken::symbol_>::perform_lex(source, output);
		case eToken::whitespace_: return TokenTraits<eToken::whitespace_>::perform_lex(source, output);
		case eToken::newline_: return TokenTraits<eToken::newline_>::perform_lex(source, output);
		case eToken::open_paren_: return TokenTraits<eToken::open_paren_>::perform_lex(source, output);
		case eToken::closed_paren_: return TokenTraits<eToken::closed_paren_>::perform_lex(source, output);
		case eToken::comma_: return TokenTraits<eToken::comma_>::perform_lex(source, output);
		default: return Token{ eToken::invalid_,"" };
		}
	}

	static auto tokenize(std::stack<char> source) {
		std::stack<Token> output;
		// While there are tokens left in the source,based on the top character of the stack determine the next type of token we should attempt to lex.
		while (!source.empty()) {
			const char initial_char = source.top();
			auto try_lex = begin_lex(source.top());

			// If we have a valid token type, then we should lex until we reach the end of the token.
			if (try_lex != eToken::invalid_) {
				auto result_token = do_lex(try_lex, source, output);
				// If the result of the lexing is a valid token, then we should push it to the output stack.
				if (result_token.type != eToken::invalid_)
					output.push(result_token);
				// Else we have a user syntax error, the token we attempted to lex was not formatted correctly.
				else
					throw std::runtime_error("Syntax error during token construction. Attempting to lex: " + token_to_string(try_lex) + " but got literal: " + result_token.lit + "\n");
			}
			// Else we have a character that is not a part of the Candi language syntax in the source code.
			else {
				std::string error = "Invalid character at start of token. Offending character: " + std::to_string(initial_char);
				throw std::runtime_error(error);
			}
		}

		return meta::reverse_stack(output);
	}

	// Phase 2
	template<> struct TokenTraits<eToken::integer_literal_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::integer_literal_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			/*	Top of source is expected to be a number_ token.
							Return an integer_literal_ token with the literal.
										*/
			Token token = source.top();
			source.pop();

			return Token{ token_type_v,token.lit };
		}
	};

	template<> struct TokenTraits<eToken::comment_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::comment_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
		/*	Top of source is expected to be a symbol containing a "//" literal.
			If the literal is not a "//" literal, then we should decompose the literal into three tokens.
				1. Pop the top of the source stack and store it.
				2. Get the position of the "//" in the literal.
				3. Decompose the literal into three tokens.
					3.1. The first token is the literal symbol before the "//".
					3.2. The second token is the literal symbol after "//".
					3.3. The third token is the literal symbol '//'.
				4. Push the three tokens back onto the source stack.
				5. Return a none_ token to indicate no token is to be pushed onto the output stack. 
				6. Continue combine.
			Else we have a "//" literal. 
				1. Consume tokens until we reach a newline.
				2. Return a comment_ token with the literal.
		*/
			Token token = source.top();
			source.pop();

			if (token.lit != DOUBLE_FORWARD_SLASH) {
				auto pos = token.lit.find(DOUBLE_FORWARD_SLASH);

				if (pos == std::string::npos) // If this occured then we have a programmer logic error.
					throw TokenCombineCriticalProgrammerLogicError(
						"[TokenCombineCriticalProgrammerLogicError]"
						"TokenTraits<eToken::comment_>::perform_combine : Could not find \"//\" in literal of top() Token on source stack.");


				auto lhs = token.lit.substr(0, pos);
				auto rhs = token.lit.substr(pos + 2, token.lit.size());
				auto middle = token.lit.substr(pos, 2);

				source.push(Token{ eToken::symbol_,lhs });
				source.push(Token{ eToken::symbol_,middle });
				source.push(Token{ eToken::symbol_,rhs });
				
				return Token{ eToken::empty_,"" };
			}
			else { 
				std::string literal;
				while (!source.empty() && !meta::one_of(source.top().type, { eToken::newline_ })) {
					literal += source.top().lit;
					source.pop();
				}
				return Token{ token_type_v,literal };
			}
		}
	};

	template<> struct TokenTraits<eToken::operator_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::operator_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			/*	Top of source is expected to be an unrecognized phase 1 symbol.
				Return an operator_ token with the literal.
			*/
			Token token = source.top();
			source.pop();

			return Token{ token_type_v,token.lit };

		}
	};

	template<> struct TokenTraits<eToken::directive_literal_operator_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::directive_literal_operator_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			/*	Top of source is expected to be a symbol containing a "#" literal.
				If the literal is not a "#" literal, then we should decompose the literal into two tokens.
					1. Pop the top of the source stack and store it.
					2. Get the position of the "#" in the literal.
					3. Decompose the literal into two tokens.
						3.1. The first token is the literal symbol before the "#".
						3.2. The second token is the literal symbol after "#". 
							3.2.1. If there is a symbol after the "#" then it is an invalid token.
							3.2.2. Else continue decomposing the literal.
						3.3. Push the tokens back onto the source stack.
						3.4. Return a none_ token to indicate no token is to be pushed onto the output stack. 
						3.5. Continue combine.
				Else we have a "#" literal. 
					1. Consume the token.
					2. Check if the following token is an alnumus token.
						2.1. If it is not an alnumus token, then we have a user syntax error.
						2.2. Else we have a potentially have a valid directive token.
							2.2.1. If the alnumus token is not a valid compiler directive keyword.
								2.2.1.1. Then we have a user syntax error - specifically an invalid keyword.
								2.2.1.2. Else we have a valid compiler directive keyword. Continue.
							2.2.1. Consume the alnumus token.
							2.2.2. Return a directive_literal_operator_ token with the literal.
			*/
			Token token = source.top();

			if (token.lit != meta::string_from_char(HASHTAG)) {
				source.pop();

				auto pos = token.lit.find(HASHTAG);

				if (pos == std::string::npos) // If this occured then we have a programmer logic error.
					throw TokenCombineCriticalProgrammerLogicError(
						"[TokenCombineCriticalProgrammerLogicError]"
						"TokenTraits<eToken::directive_literal_operator_>::perform_combine : Could not find \"#\" in literal of top() Token on source stack.");
				
				auto lhs = token.lit.substr(0, pos);
				auto rhs = token.lit.substr(pos + 1, token.lit.size());
				auto middle = token.lit.substr(pos, 1);

				if(!rhs.empty())
					throw TokenCombineUserSyntaxError(
						"[TokenCombineUserSyntaxError]"
						"TokenTraits<eToken::directive_literal_operator_>::perform_combine : Invalid token after \"#\" in literal of top() Token on source stack.");
				
				
				source.push(Token{ eToken::symbol_,middle });
				source.push(Token{ eToken::symbol_,lhs });

				return Token{ eToken::empty_,"" };
			}
			else {
				std::string literal;
				literal += source.top().lit;
				source.pop();
				
				if(source.empty() || source.top().type != eToken::alnumus_)
					throw TokenCombineUserSyntaxError(
						"[TokenCombineUserSyntaxError]"
						"TokenTraits<eToken::directive_literal_operator_>::perform_combine : Expected an alnumus token after \"#\" in literal of top() Token on source stack.");

				if (!std::any_of(CANDIL_KEYWORD_KEYWORDS.begin(),
					CANDIL_KEYWORD_KEYWORDS.end(),
					[source](std::string keyword) { return keyword == source.top().lit; })) {
					throw TokenCombineUserDirectiveKeywordSyntaxError(source.top().lit);
				}


				literal += source.top().lit;
				source.pop();

				return Token{ token_type_v,literal };
			}
		}
	};

	template<> struct TokenTraits<eToken::identifier_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::identifier_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			// Top of source is expected to be an alnumus token.
			// Return an identifier_ token with the literal.
			Token token = source.top();
			source.pop();

			return Token{ token_type_v,token.lit };
		}
	};

	template<> struct TokenTraits<eToken::float_literal_> : public TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::float_literal_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			/*	Top of source is expected to be a number_ token.
				Top of the output stack is expected to be a float_literal_operator_ token.
				Return a float_literal_ token with the literal.
				Check for overflow.
										*/
			Token float_literal_operator_token = output.top(); 
			Token number_token = source.top();

			std::string literal_float = float_literal_operator_token.lit + number_token.lit;	
			
			// Check for overflow
			try{
				std::stof(literal_float);
			}
			catch (std::out_of_range& e) {
				throw std::runtime_error(
					std::string("[TokenCombineUserSyntaxError] TokenTraits<eToken::float_literal_>::perform_combine : Float literal overflow. Literal: " + literal_float + "\n").c_str()
				);
			}

			source.pop();
			output.pop();

			return Token{ token_type_v,literal_float };
		}
	};
	
	template<> struct TokenTraits<eToken::float_literal_operator_> : TokenTraitsBase {
		using token_type = std::integral_constant<eToken, eToken::float_literal_operator_>;
		static constexpr token_type::value_type token_type_v = token_type::value;

		static Token perform_combine(std::stack<Token>& source, std::stack<Token>& output) {
			// The top of the source is expected to be a symbol containing a "."  at the front of the literal.
			if (source.top().lit != meta::string_from_char(PERIOD)) {
				//		If the literal is not a single "." then we should decompose the literal into two tokens.
				// 		1. Pop the top of the source stack and store it.
				// 	2. Get the position of the "." in the literal.
				// 	3. Decompose the literal into two tokens.
				// 		3.1. The first token is the literal symbol  ".".
				// 		3.2. The second token is the literal symbol after ".".
				// 	4. Push the tokens back onto the source stack.
				// 	5. Return a none_ token to indicate no token is to be pushed onto the output stack.
				// 	6. Continue combine.

				Token token = source.top();
				source.pop();

				auto literal_comma = token.lit.front();
				auto literal_rhs = token.lit.substr(1, token.lit.size());

				source.push(Token{ eToken::symbol_,meta::string_from_char(literal_comma) });
				source.push(Token{ eToken::symbol_,literal_rhs });

				return Token{ eToken::empty_,"" };
			}
			else {
				// Else we have a "." literal.
				// 	1. Consume the token.
				// 	2. Check if there is a valid integer_literal_ token on the output stack.
				// 		2.1. If there is not a valid integer_literal_ token on the output stack, then we have a user syntax error.	
				// 		2.2. Else we pop the integer_literal_ token off the output stack.
				// 	3. Return a float_literal_operator_ token with the literal.

				Token token = source.top();
				source.pop();

				if(output.empty() || output.top().type != eToken::integer_literal_)
					throw TokenCombineUserSyntaxError(
						"[TokenCombineUserSyntaxError]"
						"TokenTraits<eToken::float_literal_operator_>::perform_combine : Expected an integer_literal_ token on the output stack.");

				Token integer_literal_token = output.top();
				output.pop();
				// Check for overflow
				try {
					std::string cpp_integer_literal = integer_literal_token.lit + ".f";
					std::stof(cpp_integer_literal);
				}
				catch (std::out_of_range& e) {
					throw std::runtime_error(
						std::string(
					"[TokenCombineUserSyntaxError] TokenTraits<eToken::float_literal_>::perform_combine	: Float literal overflow. Literal: " + integer_literal_token.lit + "\n").c_str()
					);
				}

				return Token{ token_type_v, integer_literal_token.lit + token.lit };
			}


		}
	};


	static auto passthrough(std::stack<Token>& source, std::stack<Token>& output) {
		Token token = source.top();
		source.pop();
		return token;
	}

	static auto begin_combine(const std::stack<Token>& source, const std::stack<Token>& output) {
		const auto & token = source.top();
		
		if (output.empty()) {
			// Only scan for non output dependent tokens.
			if (token.type == eToken::symbol_) {
				// Check the literal of the symbol token to see if it one of the following:
				//		2. If the literal is a '#' -> directive_literal_operator_
				//		3. If the literal begins with a ''' -> string_literal_
				//		4.5. if the literal begins with \\ -> comment_

				if (token.lit.find(HASHTAG) != std::string::npos)
					return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
				else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
					return TokenTraits<eToken::string_literal_>::token_type::value;
				else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
					return TokenTraits<eToken::comment_>::token_type::value;
				else
					return TokenTraits<eToken::operator_>::token_type::value;
			}
			else if (token.type == eToken::whitespace_) {
				return TokenTraits<eToken::whitespace_>::token_type::value;
			}
			else if (token.type == eToken::comma_) {
				return TokenTraits<eToken::comma_>::token_type::value;
			}
			else if (token.type == eToken::open_paren_) {
				return TokenTraits<eToken::open_paren_>::token_type::value;
			}
			else if (token.type == eToken::closed_paren_) {
				return TokenTraits<eToken::closed_paren_>::token_type::value;
			}
			else if (token.type == eToken::eof_) {
				return TokenTraits<eToken::eof_>::token_type::value;
			}
			else if (token.type == eToken::newline_) {
				return TokenTraits<eToken::newline_>::token_type::value;
			}
			else {
				return TokenTraits<eToken::invalid_>::token_type::value;
			}
		}
		else {
			// Scan the rest of the tokens.
			const auto& output_token = output.top();

			if (token.type == eToken::number_) {
				// 1.1. Check if the previous token on the output stack was a float_literal_operator_.
				//		Then we should try to combine into a float_literal_.
				if (output_token.type == eToken::float_literal_operator_) {
					return TokenTraits<eToken::float_literal_>::token_type::value;
				}
				else // 1.2. Else we should try to combine into an integer_literal_. 
					return TokenTraits<eToken::integer_literal_>::token_type::value;
			}
			else if (token.type == eToken::alnumus_) {
				// 2.1. Check if the previous token on the output stack was a directive_operator_.
				//		Then we should try to combine into a compiler directive.
				if (output_token.type == eToken::directive_literal_operator_) {
					return TokenTraits<eToken::directive_>::token_type::value;
				}
				else // 2.2. Else we should try to combine into an Identifier.
					return TokenTraits<eToken::identifier_>::token_type::value;
			}
			else if (token.type == eToken::symbol_) {
				// Check the literal of the symbol token to see if it one of the following:
				//		2. If the literal is a '#' -> directive_literal_operator_
				//		3. If the literal begins with a ''' -> string_literal_
				//		4.5. if the literal begins with \\ -> comment_

				// Tokens that require a peek at the output stack.
				//if (!output.empty()) {
					if (token.lit.front() == '.' && output_token.type == eToken::integer_literal_)
						return TokenTraits<eToken::float_literal_operator_>::token_type::value;
					else if (token.lit.find(HASHTAG) != std::string::npos)
						return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
					else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
						return TokenTraits<eToken::string_literal_>::token_type::value;
					else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
						return TokenTraits<eToken::comment_>::token_type::value;
					else
						return TokenTraits<eToken::operator_>::token_type::value;
				//}

				//if (token.lit.find(HASHTAG) != std::string::npos)
				//	return TokenTraits<eToken::directive_literal_operator_>::token_type::value;
				//else if (token.lit.find(SINGLE_QUOTE) != std::string::npos)
				//	return TokenTraits<eToken::string_literal_>::token_type::value;
				//else if (token.lit.find(DOUBLE_FORWARD_SLASH) != std::string::npos)
				//	return TokenTraits<eToken::comment_>::token_type::value;
				//else
				//	return TokenTraits<eToken::operator_>::token_type::value;
			}
			else if (token.type == eToken::whitespace_) {
				return TokenTraits<eToken::whitespace_>::token_type::value;
			}
			else if (token.type == eToken::newline_) {
				return TokenTraits<eToken::newline_>::token_type::value;
			}
			else if (token.type == eToken::eof_) {
				return TokenTraits<eToken::eof_>::token_type::value;
			}
			else if (token.type == eToken::open_paren_) {
				return TokenTraits<eToken::open_paren_>::token_type::value;
			}
			else if (token.type == eToken::closed_paren_) {
				return TokenTraits<eToken::closed_paren_>::token_type::value;
			}
			else if (token.type == eToken::comma_) {
				return TokenTraits<eToken::comma_>::token_type::value;
			}
			else {
				return TokenTraits<eToken::invalid_>::token_type::value;
			}
		}
	}

	static constexpr auto do_combine(eToken token,const std::string & literal, std::stack<Token>& source, std::stack<Token>& output) {
		switch (token) {
		// Phase 1 Tokens which will pass-through to the output stack.
		case eToken::whitespace_: return passthrough(source, output);
		case eToken::newline_: return passthrough(source, output);
		case eToken::open_paren_: return passthrough(source, output);
		case eToken::closed_paren_: return passthrough(source, output);
		case eToken::comma_: return passthrough(source, output);
		case eToken::eof_: return passthrough(source, output);
		
		// Phase 2 Tokens
		case eToken::comment_: return TokenTraits<eToken::comment_>::perform_combine(source, output);
		case eToken::operator_: return TokenTraits<eToken::operator_>::perform_combine(source, output);
		case eToken::directive_literal_operator_: return TokenTraits<eToken::directive_literal_operator_>::perform_combine(source, output);
		case eToken::identifier_: return TokenTraits<eToken::identifier_>::perform_combine(source, output);
		case eToken::integer_literal_: return TokenTraits<eToken::integer_literal_>::perform_combine(source, output);
		case eToken::float_literal_: return TokenTraits<eToken::float_literal_>::perform_combine(source, output);
		case eToken::float_literal_operator_: return TokenTraits<eToken::float_literal_operator_>::perform_combine(source, output);
		//case eToken::string_literal_: return TokenTraits<eToken::string_literal_>::perform_combine(source, output);
		//case eToken::directive_: return TokenTraits<eToken::directive_>::perform_combine(source, output);
		//case eToken::operator_: return TokenTraits<eToken::operator_>::perform_combine(source, output);
		//case eToken::start_scope_: return TokenTraits<eToken::start_scope_>::perform_combine(source, output);
		//case eToken::end_scope_: return TokenTraits<eToken::end_scope_>::perform_combine(source, output);
		//case eToken::separator_: return TokenTraits<eToken::separator_>::perform_combine(source, output);
		//case eToken::identifier_: return TokenTraits<eToken::identifier_>::perform_combine(source, output);
		//case eToken::comment_: return TokenTraits<eToken::comment_>::perform_combine(source, output);
		//case eToken::float_literal_operator_: return TokenTraits<eToken::float_literal_operator_>::perform_combine(source, output);
		//case eToken::directive_literal_operator_: return TokenTraits<eToken::directive_literal_operator_>::perform_combine(source, output);

		default:
			if (token != eToken::invalid_) {
				std::cout << "[WARNING] TokenTraits<eToken::invalid_>::perform_combine : Unimplemented token type attempted to do_combine: " << token_to_string(token) << "\n\n";
			}
			return Token{ eToken::invalid_,"" };
		}
	}

	static auto combine_tokens(std::stack<Token> source) {
		std::stack<Token> output;
		while (!source.empty()) {
			const Token initial_token = source.top();
			auto try_combine = begin_combine(source,output);
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
					throw std::runtime_error("Syntax error during token construction. Attempting to combine: " + token_to_string(try_combine) + " but got "+ token_to_string(result_token.type) + " literal: " + result_token.lit + "\n");
			}
			// Else we have a token that is not a part of the Candi language syntax in the source code.
			else {
				std::string error = "Invalid character at start of token. Offending token: " + token_to_string(initial_token.type);
				throw std::runtime_error(error);
			}
		}
		return meta::reverse_stack(output);
	} // end combine_tokens

	// Phase 3 Sanitization
	// All insignificant tokens should be removed from the token stream to streamline the parsing process.
	// Insignificant tokens are:
	//		1. Whitespace
	//		2. Newline
	//		3. Comments
	// Convert the newline tokens into an end_of_statement_ token.

	static auto sanitize_tokens(std::stack<Token> source) {
		std::stack<Token> output;
		while (!source.empty()) {
			const Token initial_token = source.top();
			if (initial_token.type == eToken::whitespace_) {
				source.pop();
			}
			else if (initial_token.type == eToken::comment_) {
				source.pop();
			}
			else if (initial_token.type == eToken::newline_) {
				// If the output stack contains a end_of_statement then this is a repeated newline - insignificant.
				if (!output.empty() && output.top().type == eToken::eos_) {
					source.pop();
				}
				// if the output stack is empty, theen this statement is redundant as it contains nothing.
				else if (output.empty()) {
					source.pop();
				}
				else {
					output.push(Token{ eToken::eos_,"" });
					source.pop();
				}
			}
			else {
				output.push(initial_token);
				source.pop();
			}
		}
		return meta::reverse_stack(output);
	}

	// Phase 4 Parsing - Convert the token stream into an AST.
	enum class eStatement {
		statement_,				// A statement is a single line of code.	
		expression_,			// An expression is a statement that returns a value.
		declaration_,			// A declaration is a statement that does not return a value.
		program_,				// A program is a collection of statements.
		compiled_program_,
		interpreted_program_,

		// Declarations
		method_declaration_,	// A method declaration creates a method identifier and signature. (not necesseraliy a definition)
		variable_declaration_,	// A variable declaration creates a variable identifier and type. (not necessarily a definition)

		type_expression_,		// Returns a type.
		identifier_expression_,	// Returns an identifier.
		value_expression_,		// Returns a value. Which may be one of variable or literal expression.
		variable_expression_,	// Returns a variable which cannot be determined at compile time.
		literal_expression_,	// Returns a literal value. Always determined at compile time.

		// Literals
		literal_value_,			// A literal value is a declaration that defines a literal value.

		variable_definition_,	// A variable definition is a declaration that defines a variable.
		method_definition_,		// A method definition is a declaration that defines a method.


	};
	
	struct Statement {
		eStatement type;			// The type of statement.
		std::list<Statement> body;	// The body of the statement which recursively contains statements.
		std::vector<Token>::const_iterator beg;			// The beginning of the statement.
		std::vector<Token>::const_iterator end;			// One token past the end of the statement.


		Statement (eStatement type) :
			type(type) {}

		// Get the tokens that make up the statement in the source code.
		constexpr std::vector<Token> get_tokens(const std::vector<Token> & token_array) {
			return std::vector<Token>(beg,end);
		}

		// Get the a vector of literals of the tokens that make up this statement.
		constexpr std::vector<std::string> get_literals(const std::vector<Token>& token_array) {
			std::vector<std::string> literals;
			for (auto& token : get_tokens(token_array)) {
				literals.push_back(token.lit);
			}
			return literals;
		}

		// Get a string representation of the statement.
		constexpr std::string to_string(const std::vector<Token>& token_array) {
			std::string statement_string = "";
			for (auto& token : get_tokens(token_array)) {
				statement_string += token.lit;
			}
			return statement_string;
		}

		// Check if the body of the statement is empty.
		bool is_empty() {
			return body.empty();
		}

		// Check if the body of the statement is a literal_value declaration.
		bool is_literal_value() {
			return !is_empty()
				&& body.front().type == eStatement::literal_value_;
		}

		//  Adds a statement to the body of the statement.
		auto& add_statement(Statement statement) {
			body.push_back(statement);
			return body.back();
		}
	
	};
	


	class ParsingProcess {
		using identifier_map = std::vector<std::pair<std::string, std::any>>;
		identifier_map global_identifiers;

		// Given a token, returns the literal value of the token.
		
		std::any get_literal_value(Token token, const identifier_map & local_identifiers) {
			if(token.type == eToken::integer_literal_)
				return std::stoi(token.lit);
			else if (token.type == eToken::float_literal_)
				return std::stof(token.lit);
			else if (token.type == eToken::float_literal_operator_)
				return std::stof(token.lit);
			else if (token.type == eToken::string_literal_)
				return token.lit;
			else if (token.type == eToken::identifier_) {
				// if the token is an identifier look it up in the global identifiers map.
				auto it = std::find_if(global_identifiers.begin(), global_identifiers.end(),
					[token](std::pair<std::string, std::any> identifier) 
					{ return identifier.first == token.lit; });
				if (it != global_identifiers.end())
					return it->second;
				else {
					// Check the local identifiers map
					auto it = std::find_if(local_identifiers.begin(), local_identifiers.end(),
												[token](std::pair<std::string, std::any> identifier)
											{ return identifier.first == token.lit; });
					if (it != local_identifiers.end())
						return it->second;
					else
						return std::nullopt;
				}
			}
			else
				return std::nullopt;
		}

	};



	static Statement parse_tokens(std::stack<Token> source) {
		// Create a vector of tokens from the source stack.(constant, used for viewing)
		const std::vector<Token> source_array = [&source]()->std::vector<Token> {
			std::vector<Token> tk_array;
			while (!source.empty()) {
				tk_array.push_back(source.top());
				source.pop();
			}
			//std::reverse(tk_array.begin(), tk_array.end());
			return tk_array; }();

		auto curr_cursor = 0; // start at beggining of source.
		auto beg_cursor = 0;
		auto end_cursor = source_array.size();
		// Begin parsing the tokens.
		// 1. Root statement is always of type program_.
		//	  The beginning of the root statement is the beginning of the source.
		//	  The end of the root statement is the end of the source.
		auto root = Statement{ eStatement::program_ };
		root.beg = beg_cursor;
		root.end = end_cursor;

		// 2. First token of program must be a #enter directive, followed by a scope.
		if (source_array[curr_cursor].type != eToken::directive_literal_operator_ || source_array[curr_cursor].lit != "#enter")
			throw std::runtime_error("Syntax error during parsing. Expected #enter directive at start of program.\n");

		curr_cursor++;

		// 3. #enter directive must be followed by a scope.
		if (source_array[curr_cursor].type != eToken::open_paren_)
			throw std::runtime_error("Syntax error during parsing. Expected scope after #enter directive.\n"); 

		// 4. All tokens from this point on until the matching end scope are statements in the compiled program.
		auto& compiled_program = root.add_statement(Statement{ eStatement::compiled_program_ });
		auto scope_depth = 0;
		auto last_open_paren = curr_cursor;
		auto last_closed_paren = curr_cursor;

		for (auto i = curr_cursor; i < source_array.size(); i++) {
			auto& token = source_array[i];
			if (token.type == eToken::open_paren_) {
				// Based on the size of the open paren, we can determine how many scopes are being opened.
				scope_depth += token.lit.size();
				last_open_paren = i;
			}
			else if (token.type == eToken::closed_paren_) {
				scope_depth -= token.lit.size();
				last_closed_paren = i;
			}

			if (scope_depth == 0) {
				end_cursor = i+1;
				break;
			}
		}	

		if (scope_depth != 0) {
			std::cout << "[Mismatched parenthesis error]\n";
			std::cout << "curr_cursor: " << curr_cursor << "\n";
			std::cout << "scope_depth: " << scope_depth << "\n";
			std::cout << "last_open_paren: " << last_open_paren << "\n";	
			std::cout << "last_closed_paren: " << last_closed_paren << "\n";
			throw std::runtime_error("Syntax error during parsing. Expected matching end scope after #enter directive.\n");
		}

		compiled_program.beg = curr_cursor;
		compiled_program.end = end_cursor;

		// Move the cursor to the end of the compiled program.
		curr_cursor = end_cursor;

		// if the next token is an end of statement then ignore and continue.
		if (source_array[curr_cursor].type == eToken::eos_)
			curr_cursor++;

		// 5. The next token must be a #start directive, followed by a scope.
		if (source_array[curr_cursor].type != eToken::directive_literal_operator_ || source_array[curr_cursor].lit != "#start")
			throw std::runtime_error("Syntax error during parsing. Expected #start directive after compiled program.\n");

		curr_cursor++;

		// 6. #start directive must be followed by a scope.
		if (source_array[curr_cursor].type != eToken::open_paren_)
			throw std::runtime_error("Syntax error during parsing. Expected scope after #start directive.\n");

		// 7. All tokens from this point on until the matching end scope are statements in the interpreted program.
		auto& interpreted_program = root.add_statement(Statement{ eStatement::interpreted_program_ });
		scope_depth = 0;
		last_open_paren = curr_cursor;
		last_closed_paren = curr_cursor;

		for (auto i = curr_cursor; i < source_array.size(); i++) {
			auto& token = source_array[i];
			if (token.type == eToken::open_paren_) {
				// Based on the size of the open paren, we can determine how many scopes are being opened.
				scope_depth += token.lit.size();
				last_open_paren = i;
			}
			else if (token.type == eToken::closed_paren_) {
				scope_depth -= token.lit.size();
				last_closed_paren = i;
			}

			if (scope_depth == 0) {
				end_cursor = i + 1;
				break;
			}
		}

		if (scope_depth != 0) {
			std::cout << "[Mismatched parenthesis error]\n";
			std::cout << "curr_cursor: " << curr_cursor << "\n";
			std::cout << "scope_depth: " << scope_depth << "\n";
			std::cout << "last_open_paren: " << last_open_paren << "\n";
			std::cout << "last_closed_paren: " << last_closed_paren << "\n";
			throw std::runtime_error("Syntax error during parsing. Expected matching end scope after #start directive.\n");
		}

		interpreted_program.beg = curr_cursor;
		interpreted_program.end = end_cursor;

		// Move the cursor to the end of the interpreted program.

		curr_cursor = end_cursor;


		// Now we can begin to parse the compiled program's statements.
		for (auto it = source_array.cbegin() + compiled_program.beg; it != source_array.cbegin() + compiled_program.end; it++) {

			// 1. If the token is a directive_literal_operator_ then we should begin parsing a directive.
			if (it->type == eToken::directive_literal_operator_) {

				// If the directive literal operator is not a known directive, then we have a user syntax error.
				if (!std::any_of(CANDIL_KEYWORD_KEYWORDS.begin(),
					CANDIL_KEYWORD_KEYWORDS.end(),
					[it](std::string keyword) { return keyword == it->lit; })) {
					throw std::runtime_error("Syntax error during parsing. Invalid directive keyword: " + it->lit + "\n");
				}

				// Else determine the type of directive and create a statement based on the type.
				auto keyword = it->lit.substr(1, it->lit.size());


				// 1.1. If the directive is a #enter directive, then we should begin parsing a scope.
				if (keyword == CANDIL_KEYWORD_BREAK) {
					throw std::runtime_error("Break directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_CALL) {
					throw std::runtime_error("Call directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_CONTINUE) {
					throw std::runtime_error("Continue directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_DEFINE) {
					throw std::runtime_error("Define directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_ELIF) {
					throw std::runtime_error("Elif directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_ELSE) {
					throw std::runtime_error("Else directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_ENTER) {
					throw std::runtime_error("Enter directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_FOR) {
					throw std::runtime_error("For directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_FORIF) {
					throw std::runtime_error("Forif directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_IF) {
					throw std::runtime_error("If directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_INTO) {
					throw std::runtime_error("Into directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_METHOD) {
					// We have a MethodDeclaration.
					it++;
					// We are expecting a scope.
					if (it->type != eToken::open_paren_)
						throw std::runtime_error("Syntax error during parsing. Expected scope after #method directive.\n");
					// We have a scope
					it++;
					// Create a MethodDeclaration statement.
					auto& method_declaration = compiled_program.add_statement(Statement{ eStatement::method_declaration_ });
					method_declaration.beg = std::distance(source_array.begin(), it);
					// From the start of the scope until the first occurence of a separator(comma) token, we have a IdentifierExpression.
					auto identifier_expression_begin = it;
					while (it->type != eToken::comma_) {
						// Move the cursor to the next token.
						it++;
					}
					// We have a separator token. End of the IdentifierExpression. add it to the MethodDeclaration.
					it++; // end is the comma ( 1 past the end)

					// Create an IdentifierExpression statement.
					auto& identifier_expression = method_declaration.add_statement(Statement{ eStatement::identifier_expression_ });
					identifier_expression.beg = std::distance(source_array.begin(), identifier_expression_begin);
					identifier_expression.end = std::distance(source_array.begin(), it);

					// From the end of the IdentifierExpression until the first occurence of a separator(comma) token, we have a TypeExpression.
					auto type_expression_begin = it;
					while (it->type != eToken::comma_) {
						// Move the cursor to the next token.
						it++;
					}
					// We have a separator token. End of the TypeExpression. add it to the MethodDeclaration.
					it++; // end is the comma ( 1 past the end)

					// Create an TypeExpression statement.
					auto& type_expression = method_declaration.add_statement(Statement{ eStatement::type_expression_ });
					type_expression.beg = std::distance(source_array.begin(), type_expression_begin);
					type_expression.end = std::distance(source_array.begin(), it);

					// From the end of the TypeExpression until the first occurence of a closed_paren token, we have a value_expression_.
					auto value_expression_begin = it;
					while (it->type != eToken::closed_paren_) {
						// Move the cursor to the next token.
						it++;
					}
					// We have a closed_paren token. End of the value_expression_. add it to the MethodDeclaration.
					it++; // end is the closed_paren ( 1 past the end)

					// Create an value_expression_ statement.
					auto& value_expression = method_declaration.add_statement(Statement{ eStatement::value_expression_ });
					value_expression.beg = std::distance(source_array.begin(), value_expression_begin);
					value_expression.end = std::distance(source_array.begin(), it);

					// expect the following token to be an end of statement or a open_paren.
					if (it->type == eToken::eos_) { // This is the end of the MethodDeclaration.
						it++;
						method_declaration.end = std::distance(source_array.begin(), it);
					}
					else if (it->type == eToken::open_paren_) { // We have a MethodDefinition
						it++;
					}
					else {
						throw std::runtime_error("Syntax error during parsing. Expected end of statement or method body after method declaration.\n");
					}

					


				}
				else if (keyword == CANDIL_KEYWORD_PRINT) {
					throw std::runtime_error("Print directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_RETURN) {
					throw std::runtime_error("Return directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_START) {
					throw std::runtime_error("Start directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_TYPE) {
					throw std::runtime_error("Type directive keyword not implemented error during parsing. \n");
				}
				else if (keyword == CANDIL_KEYWORD_WHILE) {
					throw std::runtime_error("While directive keyword not implemented error during parsing. \n");
				}
				// 1.2. Else we have a user syntax error.
				else {
					throw std::runtime_error("Syntax error during parsing. Unknown candil directive keyword. \n");
				}
			}
		}

		return root;
	}


} // end namespace candi


TEST(TestCaseName, TestName) {
	//for (auto& line : CANDIL_SOURCE) {
	//	std::cout << line << std::endl;
	//}
	//meta::svarray_to_string(CANDIL_SOURCE)
	auto output = candi::tokenize(meta::sv_to_stack("#enter( )\n#start(  )"));

	//auto output = candi::tokenize(meta::sv_to_stack(meta::svarray_to_string(CANDIL_SOURCE)));
	// Print the output
	//std::string token_list = "";
	//while (!output.empty()) {
	//	auto token = output.top();
	//	output.pop();
	//	token_list += "|" + token.lit;
	//}
	//std::cout << token_list << std::endl;
	auto compound = candi::combine_tokens(output);
	auto sanitized = candi::sanitize_tokens(compound);
	// Build the AST
	auto ast = candi::parse_tokens(sanitized);

	// Print the compound output
	std::string token_list = "";
	while (!compound.empty()) {
		auto token = compound.top();
		compound.pop();
		token_list += "|" + token.lit ;
	}
	std::cout << token_list << std::endl;


	// Print the sanitized output

	token_list = "";
	while (!sanitized.empty()) {
		auto token = sanitized.top();
		sanitized.pop();
		token_list += "| l:" + token.lit + ",t:" + candi::token_to_string(token.type);
		if(token.type == candi::eToken::eos_)
			token_list += "\n";
	}
	std::cout << token_list << std::endl;





}