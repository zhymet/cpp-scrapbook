#include <initializer_list> // std::initializer_list implicit use
#include <array> // std::array 
#include <limits> // std::numeric_limits
#include <algorithm> // std::any_of
#include <string> // std::string
#include <string_view> // std::string_view
#include <vector>
#include <iterator>

//The following chart contains all 128 ASCII decimal(dec), octal(oct), hexadecimal(hex) and character(ch) codes.

//	dec	oct	hex	ch		dec	oct	hex	ch			dec	oct	hex	ch		dec	oct	hex	ch
//	0	0	00	NUL(null)	32	40	20	(space)	64	100	40	@		96	140	60	`
//	1	1	01	SOH(start of header)			33	41	21	!		65	101	41	A		97	141	61	a
//	2	2	02	STX(start of text)				34	42	22	"		66	102	42	B		98	142	62	b
//	3	3	03	ETX(end of text)				35	43	23	#		67	103	43	C		99	143	63	c
//	4	4	04	EOT(end of transmission)		36	44	24	$		68	104	44	D		100	144	64	d
//	5	5	05	ENQ(enquiry)					37	45	25 %		69	105	45	E		101	145	65	e
//	6	6	06	ACK(acknowledge)				38	46	26 &		70	106	46	F		102	146	66	f
//	7	7	07	BEL(bell)						39	47	27	'		71	107	47	G		103	147	67	g
//	8	10	08	BS(backspace)					40	50	28	(		72	110	48	H		104	150	68	h
//	9	11	09	HT(horizontal tab)				41	51	29)			73	111	49	I		105	151	69	i
//	10	12	0a	LF(line feed - new line)		42	52	2a *		74	112	4a	J		106	152	6a	j
//	11	13	0b	VT(vertical tab)				43	53	2b +		75	113	4b	K		107	153	6b	k
//	12	14	0c	FF(form feed - new page)		44	54	2c,			76	114	4c	L		108	154	6c	l
//	13	15	0d	CR(carriage return)				45	55	2d -		77	115	4d	M		109	155	6d	m
//	14	16	0e	SO(shift out)					46	56	2e	.		78	116	4e	N		110	156	6e	n
//	15	17	0f	SI(shift in)					47	57	2f /		79	117	4f	O		111	157	6f	o
//	16	20	10	DLE(data link escape)			48	60	30	0		80	120	50	P		112	160	70	p
//	17	21	11	DC1(device control 1)			49	61	31	1		81	121	51	Q		113	161	71	q
//	18	22	12	DC2(device control 2)			50	62	32	2		82	122	52	R		114	162	72	r
//	19	23	13	DC3(device control 3)			51	63	33	3		83	123	53	S		115	163	73	s
//	20	24	14	DC4(device control 4)			52	64	34	4		84	124	54	T		116	164	74	t
//	21	25	15	NAK(negative acknowledge)		53	65	35	5		85	125	55	U		117	165	75	u
//	22	26	16	SYN(synchronous idle)			54	66	36	6		86	126	56	V		118	166	76	v
//	23	27	17	ETB(end of transmission block)	55	67	37	7		87	127	57	W		119	167	77	w
//	24	30	18	CAN(cancel)						56	70	38	8		88	130	58	X		120	170	78	x
//	25	31	19	EM(end of medium)				57	71	39	9		89	131	59	Y		121	171	79	y
//	26	32	1a	SUB(substitute)					58	72	3a	:		90	132	5a	Z		122	172	7a	z
//	27	33	1b	ESC(escape)						59	73	3b  ;		91	133	5b	[		123	173	7b{
//	28	34	1c	FS(file separator)				60	74	3c <		92	134	5c	\		124	174	7c |
//	29	35	1d	GS(group separator)				61	75	3d =		93	135	5d  ]		125	175	7d }
//	30	36	1e	RS(record separator)			62	76	3e >		94	136	5e ^		126	176	7e	~
//	31	37	1f	US(unit separator)				63	77	3f ?		95	137	5f	_		127	177	7f	DEL(delete)


using char_type = char8_t;
using const_char_type = const char_type;
using const_char_type_ptr = const char_type*;
using const_char_type_ptr_list = std::initializer_list<const_char_type_ptr>;
using const_char_list = std::initializer_list<const_char_type>;
using import_file_type = std::vector<const char>;
using string_type = std::string;
using string_view_type = std::string_view;
using all_char_array_type = std::array<char_type, std::numeric_limits<char_type>::max()>;
using all_char_array_ptr_type = std::array<const char_type *, std::numeric_limits<char_type>::max()>;

// All accepted character symbols are the characters 0 to 255.
static consteval all_char_array_type candil_char_traits_all_char_array() {
	std::array<char_type, std::numeric_limits<char_type>::max()> arr{};
	auto i = std::numeric_limits<char_type>::min();
	for (auto& c : arr) {
		c = i;
		i++;
	}
	return std::move(arr);
}

// All accepted character symbols are the characters 0 to 255.
static consteval auto candil_char_traits_all_char_array_ptr(const all_char_array_type& char_arr) {
	all_char_array_ptr_type arr{};
	
	const char_type * i = char_arr.data();
	for (auto& c : arr) {
		c = i;
		i++;
	}
	return std::move(arr);
}

struct CharTraits {
	using char_type = char8_t;
	using const_char_type = const char_type;
	using const_char_type_ptr = const char_type*;
	using const_char_type_ptr_list = std::initializer_list<const_char_type_ptr>;
	using const_char_list = std::initializer_list<const_char_type>;
	using import_file_type = std::vector<const char>;
	using string_type = std::string;
	using string_view_type = std::string_view;

	static constexpr const auto ALL_CHAR_ARRAY = candil_char_traits_all_char_array();
	static constexpr const auto ALL_CHAR_POINTER = candil_char_traits_all_char_array_ptr(ALL_CHAR_ARRAY);

	static constexpr const_char_list ALL = const_char_list(ALL_CHAR_ARRAY.data(), ALL_CHAR_ARRAY.data() + ALL_CHAR_ARRAY.size());
	static constexpr const_char_list ALPHABETIC_CHARACTERS = {
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	static constexpr const_char_list ALNUMUS_CHARACTERS = {
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'_','0','1','2','3','4','5','6','7','8','9'
	};
	static constexpr const_char_list NUMERIC_CHARACTERS = {
	'0','1','2','3','4','5','6','7','8','9'
	};
	static constexpr const_char_list CORE_SYMBOL_CHARACTERS = {
		'!','@','#','$','%','^','&','*','-','+','=','{','}','[',']','|','\\',';',':','\'','\"','<','>','?','/','~','`','.',',','(',')','_'
	};
	static constexpr const_char_list EXTENDED_SYMBOL_CHARACTERS = {
			128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
			144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
			160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
			176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
			192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
			208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
			224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
			240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
	};
	static constexpr const_char_list SYMBOL_CHARACTERS = {
			'!','@','#','$','%','^','&','*','-','+','=','{','}','[',']','|',
			'\\',';',':','\'','\"','<','>','?','/','~','`','.',',','(',')','_',
			128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
			144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
			160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
			176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
			192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
			208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
			224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
			240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
	};
	static constexpr const_char_list WHITESPACE_CHARACTERS = {
		' ','\t','\n','\r','\v','\f'
	};
	static constexpr const_char_list NEWLINE_CHARACTERS = {
		'\n','\r','\v','\f'
	};
	static constexpr const_char_list CORE_CONTROL_CHARACTERS = {
		'\0','\a','\b','\t','\n','\v','\f','\r','\x1b'
	};

	static constexpr bool is_alpha(char_type c) {
		return std::any_of(ALPHABETIC_CHARACTERS.begin(),
			ALPHABETIC_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_numeric(char_type c) {
		return std::any_of(NUMERIC_CHARACTERS.begin(),
			NUMERIC_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_underscore(char_type c) {
		return c == '_';
	}
	static constexpr bool is_alnumus(char_type c) {
		return is_alpha(c) || is_numeric(c) || is_underscore(c);
	}
	static constexpr bool is_symbol(char_type c) {
		return std::any_of(SYMBOL_CHARACTERS.begin(),
			SYMBOL_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_core_symbol(char_type c) {
		return std::any_of(CORE_SYMBOL_CHARACTERS.begin(),
			CORE_SYMBOL_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_extended_symbol(char_type c) {
		return std::any_of(EXTENDED_SYMBOL_CHARACTERS.begin(),
			EXTENDED_SYMBOL_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_printable_space(char_type c) {
		return c == ' ' || c == '\t';
	}
	static constexpr bool is_printable(char_type c) {
		return is_alpha(c) || is_numeric(c) || is_core_symbol(c) || is_printable_space(c);
	}
	static constexpr bool is_whitespace(char_type c) {
		return std::any_of(WHITESPACE_CHARACTERS.begin(),
			WHITESPACE_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_newline(char_type c) {
		return std::any_of(NEWLINE_CHARACTERS.begin(),
			NEWLINE_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
	static constexpr bool is_core_control(char_type c) {
		return std::any_of(CORE_CONTROL_CHARACTERS.begin(),
			CORE_CONTROL_CHARACTERS.end(),
			[c](const_char_type match) { return match == c; });
	}
};

// A character type that can be used to represent all characters in the source code.
struct Char {
	char_type val{};
	const_char_type_ptr ptr{};

	constexpr Char(char_type value) : val(value), ptr(CharTraits::ALL_CHAR_POINTER[value]) {}
	constexpr Char(const_char_type_ptr ptr) : val(*ptr), ptr(ptr) {}
	constexpr Char() : val('\0'), ptr(CharTraits::ALL_CHAR_POINTER[0]) {}

	constexpr bool is_alpha()const {
		return CharTraits::is_alpha(val);
	}
	constexpr bool is_numeric()const {
		return CharTraits::is_numeric(val);
	}
	constexpr bool is_underscore()const {
		return CharTraits::is_underscore(val);
	}
	constexpr bool is_alnumus()const {
		return CharTraits::is_alnumus(val);
	}
	constexpr bool is_symbol()const {
		return CharTraits::is_symbol(val);
	}
	constexpr bool is_core_symbol()const {
		return CharTraits::is_core_symbol(val);
	}
	constexpr bool is_extended_symbol()const {
		return CharTraits::is_extended_symbol(val);
	}
	constexpr bool is_printable_space()const {
		return CharTraits::is_printable_space(val);
	}
	constexpr bool is_printable()const {
		return CharTraits::is_printable(val);
	}
	constexpr bool is_whitespace()const {
		return CharTraits::is_whitespace(val);
	}
	constexpr bool is_newline()const {
		return CharTraits::is_newline(val);
	}
	constexpr bool is_core_control()const {
		return CharTraits::is_core_control(val);
	}
};

//namespace ePhase2Token {
//	using enum_type = std::uint8_t;
//	enum ePhase2Token : std::uint8_t {
//		// All Phases
//		invalid_,				// Invalid token. Used to indicate a syntax error.
//		none_,					// No token. Used to no token is required.
//
//		line_comment_,			// Comment token. eg. "''"
//		block_comment_,			// Comment token. eg. "'''"
//		integral_,				// Integral literal value 1234
//		real_,					// real literal value 1234.5678
//		string_,				// String literal value. 'hello'
//		identity_,				// Identity value. eg. hello_world
//		directive_,				// # followed by a directive name #define
//		end_of_statement_,		//
//		open_scope_,			// '('
//		closed_scope_,          // ')'
//		open_type_scope_,		// '<'
//		closed_type_scope_,		// '>'
//		open_list_scope_,		// '{'
//		closed_list_scope_,		// '}'
//
//		// Binary operators
//		operator_plus_,			// '+'
//		operator_minus_,		// '-'
//		operator_multiply_,		// '*'
//		operator_divide_,		// '/'
//		operator_modulo_,		// '%'
//
//		// Unrary operators
//		operator_pre_increment_,	// '++'
//		operator_pre_decrement_,	// '--'
//		operator_post_increment_,	// '++'
//		operator_post_decrement_,	// '--'
//		operator_negative_,			// '-'
//		operator_flip_,				// '~'
//
//		// Assignment operators
//		operator_assign_,			// '='
//		operator_plus_assign_,		// '+='
//		operator_minus_assign_,		// '-='
//		operator_multiply_assign_,	// '*='
//		operator_divide_assign_,	// '/='
//		operator_modulo_assign_,	// '%='
//
//		// Comparison operators
//		operator_equal_,			// '=='
//		operator_not_equal_,		// '!='
//		operator_less_,				// '<'
//		operator_greater_,			// '>'
//		operator_less_equal_,		// '<='
//		operator_greater_equal_,	// '>='
//
//		// Logical operators
//		operator_logical_and_,		// '&&'
//		operator_logical_or_,		// '||'
//		operator_logical_not_,		// '!'
//		operator_logical_xor_,		// '^'
//	};
//};
//
//template<typename ArrayT,
//	typename ObjT,
//	typename EnumT,
//	typename OpenConditionT, 
//	typename CloseConditionT>
//struct ParserModel {
//	using obj_type = ObjT;
//	using open_condition_type = OpenConditionT;
//	using close_condition_type = CloseConditionT;
//	using source_array_type = ArrayT;
//
//	const ArrayT & src{};
//	obj_type obj{};
//	open_condition_type open_condition{};
//	close_condition_type close_condition{};
//
//	constexpr ParserModel(ArrayT src, open_condition_type open_condition, close_condition_type close_condition) : obj(obj), open_condition(open_condition), close_condition(close_condition) {}
//	constexpr ParserModel() : obj(), open_condition(), close_condition() {}
//
//	constexpr EnumT opening(obj_type obj)const {
//		return open_condition(src,obj);
//	}
//	constexpr bool closing(EnumT obj_type)const {
//		return close_condition(src,obj);
//	}
//
//
//};
//
//// A specific character in the source code.
//struct P1Parser {
//
//
//	// Returns the type of token this character would open.
//	constexpr ePhase1Token::enum_type opening(const Char & c)const  {
//		if (is_numeric()) {
//			return ePhase1Token::number_;
//		}
//		else if (is_alpha()) {
//			return ePhase1Token::alnumus_;
//		}
//		else if (is_whitespace()) {
//			return ePhase1Token::whitespace_;
//		}
//		else if (is_newline()) {
//			return ePhase1Token::newline_;
//		}
//		else if (value == '\0') {
//			return ePhase1Token::eof_;
//		}
//		else if (value == '@') {
//			return ePhase1Token::commercial_at_;
//		}
//		else if (is_symbol()) {
//			if (is_core_symbol()) {
//				if (value == '(') {
//					return ePhase1Token::open_paren_;
//				}
//				else if (value == ')') {
//					return ePhase1Token::closed_paren_;
//				}
//				else if (value == ',') {
//					return ePhase1Token::comma_;
//				}
//				else if (value == '.') {
//					return ePhase1Token::period_;
//				}
//				else if (value == '#') {
//					return ePhase1Token::pound_;
//				}
//				else if (value == '@') {
//					return ePhase1Token::commercial_at_;
//				}
//				else if (value == '!') {
//					return ePhase1Token::exclamation_mark_;
//				}
//				else if (value == '?') {
//					return ePhase1Token::question_mark_;
//				}
//				else if (value == '"') {
//					return ePhase1Token::quotation_mark_;
//				}
//				else if (value == '\'') {
//					return ePhase1Token::apostrophe_;
//				}
//				else if (value == ':') {
//					return ePhase1Token::colon_;
//				}
//				else if (value == ';') {
//					return ePhase1Token::semicolon_;
//				}
//				else if (value == '&') {
//					return ePhase1Token::ampersand_;
//				}
//				else if (value == '%') {
//					return ePhase1Token::percent_sign_;
//				}
//				else if (value == '*') {
//					return ePhase1Token::asterisk_;
//				}
//				else if (value == '+') {
//					return ePhase1Token::plus_sign_;
//				}
//				else if (value == '-') {
//					return ePhase1Token::minus_sign_;
//				}
//				else if (value == '/') {
//					return ePhase1Token::solidus_;
//				}
//				else if (value == '\\') {
//					return ePhase1Token::reverse_solidus_;
//				}
//				else if (value == '=') {
//					return ePhase1Token::equals_sign_;
//				}
//				else if (value == '<') {
//					return ePhase1Token::less_than_sign_;
//				}
//				else if (value == '>') {
//					return ePhase1Token::greater_than_sign_;
//				}
//				else if (value == '^') {
//					return ePhase1Token::circumflex_accent_;
//				}
//				else if (value == '_') {
//					return ePhase1Token::low_line_;
//				}
//				else if (value == '|') {
//					return ePhase1Token::vertical_line_;
//				}
//				else if (value == '~') {
//					return ePhase1Token::tilde_;
//				}
//				else if (value == '{') {
//					return ePhase1Token::left_curly_bracket_;
//				}
//				else if (value == '}') {
//					return ePhase1Token::right_curly_bracket_;
//				}
//				else if (value == '[') {
//					return ePhase1Token::left_square_bracket_;
//				}
//				else if (value == ']') {
//					return ePhase1Token::right_square_bracket_;
//				}
//				else if (value == '?') {
//					return ePhase1Token::question_mark_;
//				}
//				else if (value == '`') {
//					return ePhase1Token::left_apostrophe_;
//				}
//				else {
//					return ePhase1Token::symbol_;
//				}
//			}
//			else if (is_extended_symbol()) {
//				return ePhase1Token::symbol_;
//			}
//		}
//		else {
//			return ePhase1Token::invalid_;
//		}
//	}
//
//	// Given a token type curently open, returns true if this character would close that token.
//	constexpr bool closing(ePhase1Token::enum_type type)const {
//		switch (type)
//		{
//			case ePhase1Token::number_:
//				return !is_numeric();
//			case ePhase1Token::alnumus_:
//				return !is_alnumus();
//			case ePhase1Token::whitespace_:
//				return !is_whitespace();
//			case ePhase1Token::newline_:
//				return !is_newline();
//			// Single character tokens
//			case ePhase1Token::eof_:
//			case ePhase1Token::open_paren_:
//			case ePhase1Token::closed_paren_:
//			case ePhase1Token::comma_:
//			case ePhase1Token::period_:
//			case ePhase1Token::pound_:
//			case ePhase1Token::commercial_at_:
//			case ePhase1Token::exclamation_mark_:
//			case ePhase1Token::question_mark_:
//			case ePhase1Token::quotation_mark_:
//			case ePhase1Token::apostrophe_:
//			case ePhase1Token::colon_:
//			case ePhase1Token::semicolon_:
//			case ePhase1Token::ampersand_:
//			case ePhase1Token::percent_sign_:
//			case ePhase1Token::asterisk_:
//			case ePhase1Token::plus_sign_:
//			case ePhase1Token::minus_sign_:
//			case ePhase1Token::solidus_:
//			case ePhase1Token::reverse_solidus_:
//			case ePhase1Token::equals_sign_:
//			case ePhase1Token::less_than_sign_:
//			case ePhase1Token::greater_than_sign_:
//			case ePhase1Token::circumflex_accent_:
//			case ePhase1Token::low_line_:
//			case ePhase1Token::vertical_line_:
//			case ePhase1Token::tilde_:
//			case ePhase1Token::left_curly_bracket_:
//			case ePhase1Token::right_curly_bracket_:
//			case ePhase1Token::left_square_bracket_:
//			case ePhase1Token::right_square_bracket_:
//			case ePhase1Token::left_apostrophe_:
//				return false;
//		default:
//				return false;
//		}
//	}
//};
//
//constexpr auto get_source_file(const std::vector<const char>& import_file) {
//	source_file_type file{};
//	for (auto i = 0; i < import_file.size(); i++) {
//		file.push_back(SourceChar{ i });
//	}
//	return std::move(file);
//}
//
//struct Phase1Token {
//	ePhase1Token::enum_type type;
//	std::size_t beg;// index of the first character in the source file.
//	std::size_t end;// index of the last character in the source file.
//
//	constexpr auto literal(const source_file_type& source_file)const {
//		std::string lit;
//		for (auto i = beg; i < end; i++) {
//			lit.push_back(source_file[i].value);
//		}
//		return lit;
//	}
//
//	constexpr ePhase2Token::enum_type opening(const std::vector<Phase1Token>& source, std::vector<Phase1Token>::const_iterator it) {
//		const auto & p1tk = *it;
//		switch (p1tk.type)
//		{
//			case ePhase1Token::number_:
//				if(std::next(it)->type == ePhase1Token::period_)
//					return ePhase2Token::real_;
//				else
//					return ePhase2Token::integral_;
//			case ePhase1Token::alnumus_:
//				return ePhase2Token::identity_;
//			case ePhase1Token::whitespace_:
//				return ePhase2Token::none_;
//			case ePhase1Token::newline_:
//				return ePhase2Token::end_of_statement_;
//
//
//		}
//	}
//};
//
//std::vector<Phase1Token> phase1_tokenize(const source_file_type& source_file) {
//	std::vector<Phase1Token> tokens{};
//	std::size_t char_index = 0;
//	std::size_t token_index = 0;
//
//	while (char_index < source_file.size()) {
//		auto token_type = source_file[char_index].opening();
//		auto beg = char_index;
//
//		if (token_type == ePhase1Token::invalid_) {
//			throw std::exception("Invalid token in source file.");
//		}
//		else {
//			while (char_index < source_file.size() && !source_file[char_index].closing(token_type)) {
//				char_index++;
//			}
//
//			tokens.push_back(Phase1Token{ token_type });
//			token_index++;
//		}
//	}
//}
//
//
//
//
//struct Phase2Token {
//	ePhase1Token::enum_type type;
//	const source_file_type& src;
//	std::size_t index;
//
//	constexpr auto literal() const {
//		std::string lit;
//		for (auto i = begin.index; i < end.index; i++) {
//			lit.push_back(src[i].value);
//		}
//		return lit;
//	}
//};
//
//
//
//
//
//
//constexpr auto COMMA = ',';
//constexpr auto OPEN_PARENTHESIS = '(';
//constexpr auto CLOSED_PARENTHESIS = ')';
//constexpr auto WHITESPACE = ' ';
//constexpr auto NEWLINE = '\n';
//constexpr auto ENDFILE = '\0';
//constexpr auto TABSPACE = '\t';
//constexpr auto HASHTAG = '#';
//constexpr auto PERIOD = '.';
//constexpr auto SINGLE_QUOTE = '\'';
//constexpr auto TRIPLE_QUOTE = "\'\'\'";
//constexpr auto OPEN_ANGLE_BRACKET = '<';
//constexpr auto CLOSED_ANGLE_BRACKET = '>';
//constexpr auto DOUBLE_FORWARD_SLASH = "//";
//
//
//auto CANDIL_KEYWORD_ENTER = "enter";
//auto CANDIL_KEYWORD_START = "start";
//auto CANDIL_KEYWORD_DEFINE = "define";
//auto CANDIL_KEYWORD_METHOD = "method";
//auto CANDIL_KEYWORD_CALL = "call";
//auto CANDIL_KEYWORD_TYPE = "type";
//auto CANDIL_KEYWORD_IF = "if";
//auto CANDIL_KEYWORD_ELSE = "else";
//auto CANDIL_KEYWORD_ELIF = "elif";
//auto CANDIL_KEYWORD_WHILE = "while";
//auto CANDIL_KEYWORD_FOR = "for";
//auto CANDIL_KEYWORD_FORIF = "forif";
//auto CANDIL_KEYWORD_BREAK = "break";
//auto CANDIL_KEYWORD_CONTINUE = "continue";
//auto CANDIL_KEYWORD_RETURN = "return";
//auto CANDIL_KEYWORD_INTO = "into";
//
//auto CANDIL_KEYWORD_PRINT = "print";
//
//
//constexpr auto CANDIL_KEYWORD_KEYWORDS = {
//	// Directives
//	"enter",
//	"start",
//	"define",
//	"method",
//	"call",
//	"type",
//
//	// Control flow
//	"if",
//	"else",
//	"elif",
//	"while",
//	"for",
//	"forif",
//	"break",
//	"continue",
//	"return",
//	"into",
//
//	// Special Methods
//	"print"
//};