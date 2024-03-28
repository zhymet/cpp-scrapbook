#include <stack>
#include <any>
namespace candil_language {

	enum class Keywords {
		invalid_ = 0,
		// Directives
		enter_,
		define_,
		method_,
		call_,
        type_,

		// Types
		int_,
		float_,
		string_,
		bool_,
		void_,

		// Control flow
		if_,
		else_,
		while_,
		for_,
		break_,
		continue_,
		return_,
		into_,

		KeywordsCount
	};

	std::map<Keywords, std::string> keywords = {
		// Directives
		{Keywords::enter_, "enter"},
		{Keywords::define_, "define"},
		{Keywords::method_, "method"},
		{Keywords::call_, "call"},
		{Keywords::type_, "type"},

		// Types
		{Keywords::int_, "int"},
		{Keywords::float_, "float"},
		{Keywords::string_, "string"},
		{Keywords::bool_, "bool"},
		{Keywords::void_, "void"},

		// Control flow
		{Keywords::if_, "if"},
		{Keywords::else_, "else"},
		{Keywords::while_, "while"},
		{Keywords::for_, "for"},
		{Keywords::break_, "break"},
		{Keywords::continue_, "continue"},
		{Keywords::return_, "return"},
		{Keywords::into_, "into"},
	};

	struct Token {
		// Conditions for building the token.
		auto association() const -> int;		// Left or right, or none.
		auto precidence() const -> int;			// Higher precidence means we will evaluate it last.
		auto terminator() const -> bool;		// The token that will terminate consumption of characters for this token's literal.
		auto consumption() const -> bool;		// The type of consumption this token uses. unary, binary, variadic right, variadic left or none.
		auto is(std::string_view) const -> bool;  // true if the required literal is equal to the given string.

		// Result of building the token.
		auto popped() const -> bool;					// Characters popped from the output stack.
		auto advanced() const -> bool;					// Characters advanced in the input stack.
		auto literal() const -> std::string_view;		// The literal that was created
		auto identity() const -> std::string_view;		// The identity(hash) of the token. equal for all tokens of the same type and value.
		auto type() const -> Keywords;					// The type of this token.

		auto lex(std::stack<char> & input, std::stack<char> & output) -> Token;


	};


	struct NodeLocation {
		int beg_line;
		int end_line;
		
		int end_column;
		int beg_column;
		
		int beg_range;
		int end_range;
	};

	struct Node {
		NodeLocation loc;
	};

	struct Literal : Node {
		std::any value;
	};
		struct Object : Literal {};
		struct Integral : Literal {};
		struct Floating : Literal {};
		struct String : Literal {};
		struct Boolean : Literal {};

	struct Abstract : Node {
		std::string name;
	};
		struct Typename : Abstract {
	};
		struct Identifier : Abstract {};
		struct Scope : Abstract {};

	struct Statement : Node {
		std::vector<Statement> body;
	};

	struct Expression : Statement {
		virtual std::any solve() { return nullptr; };
		virtual std::type_index solution_type() { return typeid(void); };
	};
		struct IdentifierExpression : Expression {

	};
		struct TypeExpression : Expression {
		virtual std::type_index solution_type() { return typeid(Typename); };
	};
		struct ValueExpression : Expression {

	};

	struct Declaration : Statement {

		};
		struct VariableDeclaration : Declaration {
		TypeExpression type;
		IdentifierExpression identifier;
		ValueExpression value;
	};
		struct MethodDeclaration : Declaration {

		};
		struct ObjectDeclaration : Declaration {

		};

	struct Program : Statement {
		std::vector<Scope> scopes;
		std::vector<Typename> types;
		std::vector<Identifier> identifiers;

		std::any execute() {
			auto result = std::any(nullptr);
			for (auto& statement : body) {
				// Do things depending on the statement type.

			}

			// Return the result of the program.
			return result;
		}
	};


}