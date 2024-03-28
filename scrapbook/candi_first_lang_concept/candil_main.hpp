#include "candil.hpp"
#include <vector>
#include <functional>
#include <array>
#include <map>
#include <any>
#include <typeindex>


// Sample program transpilation output given the code below:
/*

#enter {
	#def(@,my_int,10) // Define a compile time variable called my_int with the value 10, the type is @ (auto) will infer the type from the value.

	#method(add_to_my_int, @,#type(int),argument_name) // Define a method add_to_my_int with the return type of auto and 1 arg of type in, and the argument name of argument_name.
	{
		#return(my_int += argument_name)
	}

	#call(add_to_my_int, my_int) // Call the method add_to_my_int with the argument of my_int. my_int is now 20.

}

*/

/*
	Tokens are one of:
		- Identifier
		- IntegerLiteral
		- FloatLiteral
		- StringLiteral
		- CharLiteral
		- BoolLiteral
		- AutoKeyword
		- TypeKeyword
		- MethodKeyword
		- CallKeyword
		- ReturnKeyword
		- DefKeyword
		- IfKeyword
		- ElseKeyword
		- ForKeyword
		- WhileKeyword
		- DoKeyword
		- SwitchKeyword
		- CaseKeyword
		- DefaultKeyword
		- BreakKeyword
		- ContinueKeyword
		- GotoKeyword
		- StructKeyword
		- ClassKeyword
		- EnumKeyword
		- NamespaceKeyword
		- UsingKeyword
		- PublicKeyword
		- PrivateKeyword
		- ProtectedKeyword
		- StaticKeyword
		- VirtualKeyword
		- ConstKeyword
		- VolatileKeyword
		- MutableKeyword
		- ExternKeyword
		- InlineKeyword
		- OperatorKeyword
		- FriendKeyword
		- TemplateKeyword
		- TypedefKeyword
		- TypeofKeyword
		- SizeofKeyword
		- AlignofKeyword
		- NewKeyword
		- DeleteKeyword
		- ThisKeyword
		- NullptrKeyword
		- TrueKeyword
		- FalseKeyword
		- AndKeyword
		- OrKeyword
		- NotKeyword
		- XorKeyword
		- BitAndKeyword
		- BitOrKeyword
		- BitNotKeyword
		- BitXorKeyword
		- BitLeftShiftKeyword
		- BitRightShiftKeyword
		- PlusKeyword
		- MinusKeyword
		- MultiplyKeyword
		- DivideKeyword
		- ModuloKeyword
		- IncrementKeyword
		- DecrementKeyword
		- AssignmentOperator
		- PlusAssignmentOperator
		- MinusAssignmentOperator
		- MultiplyAssignmentOperator
		- DivideAssignmentOperator
		- ModuloAssignmentOperator
		- BitAndAssignmentOperator
		- BitOrAssignmentOperator
		- BitXorAssignmentOperator
		- BitLeftShiftAssignmentOperator
		- BitRightShiftAssignmentOperator
		- EqualToOperator
		- NotEqualToOperator
		- LessThanOperator
		- GreaterThanOperator
		- LessThanOrEqualToOperator
		- GreaterThanOrEqualToOperator
		- LogicalAndOperator
		- LogicalOrOperator
		- LogicalNotOperator
		- BitAndOperator
		- BitOrOperator
		- BitXorOperator
		- BitLeftShiftOperator
		- BitRightShiftOperator
		- CommaOperator
		- DotOperator
		- ArrowOperator
		- ScopeOperator

	Sample parsed token list for this program:
	- DefKeyword
		- Identifier : 'my_int'
		- AssignmentOperator : '='
		- IntegerLiteral : '10'
	- MethodKeyword
		- Identifier : 'add_to_my_int'
		- TypeKeyword : '#type'
		- Identifier : 'int'
		- Identifier : 'argument_name'
		- BlockExpression
			- ReturnKeyword
			- Identifier : 'my_int'
			- AssignmentOperator : '+='
			- Identifier : 'argument_name'
	- CallKeyword
		- Identifier : 'add_to_my_int'
		- Identifier : 'my_int'

	Sample token list parrsing algorithm:
	1. Read the first token.
		1.1. If the token is a keyword, parse the keyword.
	2. If the token is a DefKeyword, check for a ScopeOperator. If there is a ScopeOperator, parse a variable definition. Else syntax error.
	    2.1. Read the next token until the comma operator. Add the token to the list of tokens in the TypeExpression. Add the TypeExpression to the VariableDefinition.
		2.2. Read the next token until the comma operator. Add the token to the list of tokens in the IdentifierExpression. Add the IdentifierExpression to the VariableDefinition.
		2.3. Read the next token until the comma operator. Add the token to the list of tokens in the ValueExpression. Add the ValueExpression to the VariableDefinition.

		VariableDefinition
			- TypeExpression
				- AutoKeyword : '@' auto
			- IdentifierExpression
			    - Identifier : 'my_int'
			- ValueExpression
			    - IntegerLiteral : '10'

	3. if the token is a MethodKeyword, check for a ScopeOperator. If there is a ScopeOperator, parse a method definition. Else syntax error.
		3.1. Read the next token until the comma operator. Add the token to the list of tokens in the IdentifierExpression. Add the IdentifierExpression to the MethodDefinition.
		3.2. Read the next token until the comma operator. Add the token to the list of tokens in the TypeExpression. Add the TypeExpression to the MethodDefinition.
		3.3. Read the next token until the comma operator. Add the token to the list of tokens in the TypeExpression. Add the TypeExpression to the MethodDefinition.
		3.4. Read the next token until the comma operator. Add the token to the list of tokens in the IdentifierExpression. Add the IdentifierExpression to the MethodDefinition.
		3.5. Expect a ScopeOperator. If there is a ScopeOperator, parse a block expression. Else syntax error.

		MethodDefinition
			- IdentifierExpression
			    - Identifier : 'add_to_my_int'
			- TypeExpression
				- AutoKeyword : '@' auto
			- TypeExpression
				- TypeDirective
				    - TypeKeyword : '#type'
					- TypeExpression
						- IdentifierExpression
							- Identifier : 'int'
			- IdentifierExpression
			    - Identifier : 'argument_name'
			- BlockExpression
			    - ReturnExpression
					- BinaryExpression
						- IdentifierExpression
							- Identifier : 'my_int'
						- AssignmentOperator : '+='
						- IdentifierExpression
							- Identifier : 'argument_name'
	
	4. if the token is a CallKeyword, check for a ScopeOperator. If there is a ScopeOperator, parse a method call. Else syntax error.
		4.1. Read the next token until the comma operator. Add the token to the list of tokens in the IdentifierExpression.
		4.2. Read the next token until the comma operator. Add the token to the list of tokens in the ValueExpression.

		CallDirective
			- IdentifierExpression
			    - Identifier : 'add_to_my_int'
			- ValueExpression
			   - Identifier : 'my_int'
   

*/


/* Sample AST tree

enter	->VariableDefinition
			-> TypeExpression
				-> AutoKeyword : '@' auto
			-> IdentifierExpression
			    -> Identifier : 'my_int'
			-> ValueExpression
			    -> IntegerLiteral : '10'
		->MethodDefinition
			-> IdentifierExpression
			    -> Identifier : 'add_to_my_int'
			-> TypeExpression
				-> AutoKeyword : '@' auto
			-> TypeExpression
				-> TypeDirective
				    -> TypeKeyword : '#type'
					-> TypeExpression
						-> IdentifierExpression
							-> Identifier : 'int'
			-> IdentifierExpression
			    -> Identifier : 'argument_name'
			-> BlockExpression
			    -> ReturnExpression
					-> BinaryExpression
						-> IdentifierExpression
							-> Identifier : 'my_int'
						-> AssignmentOperator : '+='
						-> IdentifierExpression
							-> Identifier : 'argument_name'
		->MethodCall
			-> IdentifierExpression
			    -> Identifier : 'add_to_my_int'
			-> ValueExpression
			    -> Identifier : 'my_int'

What is the difference between a value expression and an identifier expression?
	- A value expression is a literal value, such as an integer, string, or float.
	- An identifier expression is a reference to a variable, method, or call.

What is the difference between a type expression and a type directive?
	- A type expression is a type that is inferred from the value of a variable.
	- A type directive is a type that is explicitly defined by the user.

What is the difference between a method definition and a method call?
	- A method definition is a definition of a method.
	- A method call is a call to a method.

Sample AST tree walk:
	1. Enter the enter block. Walk from left to right.
	2. Enter the variable definition. Walk from left to right.
		2.1. Enter the type expression. See that it is an auto keyword. Infer the type from the result of the value expression.
		2.2. Enter the identifier expression. See that it is an identifier. Add the identifier to the symbol table.
		2.3. Enter the value expression. See that it is an integer literal. Assing the value to the identifier in the symbol table. 
		2.4. See that the type of the identifier is an integer. Set the type of the identifier in the symbol table to integer.
		2.5. Exit the variable definition.
	3. Enter the method definition. Walk from left to right.
		3.1. Enter the identifier expression. See that it is an identifier. Add the identifier to the symbol table.
		3.2. Enter the type expression. See that it is an auto keyword. Infer the type from the result of the type expression.
		3.3. Enter the type expression. See that it is a type directive. See that it is a type keyword. See that it is an identifier. Add the identifier to the symbol table.
		3.4. Enter the identifier expression. See that it is an identifier. Add the identifier to the local method symbol table.
		3.5. Enter the block expression. Walk from left to right.
			3.5.1. Enter the return expression. Walk from left to right.
			3.5.3. Enter the identifier expression. See that it is an identifier. Look up the identifier in the symbol tables. Set it as the left hand side of the binary expression.
			3.5.2. See the binary assingment operator. Set the previous expression as the left hand side of the binary expression.
			3.5.4. Enter the identifier expression. See that it is an identifier. Look up the identifier in the symbol tables. Set it as the right hand side of the binary expression.
			3.5.5. Add the return expression to the list of expressions in the block expression assigned to this method in the symbol table.
			3.6. Exit the method definition.
	4. Enter the method call. Walk from left to right.
		4.1. Enter the identifier expression. See that it is an identifier. Look up the identifier in the symbol tables. Set it as the callee of this call directive.
		4.2. Enter the value expression. See that it is an identifier. Look up the identifier in the symbol tables. Set it as the argument of this call directive.
		4.3. Push the call to the heap of calls to be executed.
		4.4. Exit the method call.

	5. See that there is not return statmenet in the enter block. Designate the return type as void.
	6. Execute all calls on the heap of calls to be executed.
	7. Return a value upon completion of the program. If none is specified, return nullptr.

*/
namespace candil {

	// Compile Time
	// 1. Variables are transpiled below as members.
	//		Given a #def(X,Y,Z) 
	//				return X Y = Z;	
	int my_int = 10;

	// 2. Methods are transpiled below as member methods.
	//		Given a #method(Q,X,Y1,Z1,Y2,Z2,...,YN,ZN)
	//				return Q X(Y Z, Y1 Z1, Y2 Z2, ..., YN ZN) ( ... )
	constexpr int add_to_my_int(int argument_name) {
		return my_int += argument_name;
	}

	// 3. Constant expression calls are transpiled below as bound function objects refering to a lambda expression in a vector.
	//		For each return type of a constant expression call, a vector of bound function objects is created in an index map.
		//		Given a #call(X,Y1,Y2,...,YN)
		//				[this]() { return X(Y1, Y2, ..., YN); }
	std::array<std::function<void()>, 1> enter_calls = {
		[]() { return add_to_my_int(my_int);
		}
	};


	// Runtime
// 1. Variables are transpiled as a vector of tuples of the form (type_id, name, value).
//		Given a #def(X,Y,Z)
//				return std::tuple<X, Y, Z>
	std::vector<std::tuple<std::type_index, std::string, std::any>> runtime_variables = {
		std::tuple<std::type_index, std::string, std::any>(typeid(int), "my_running_int", 20)
	};

	// 2 Runtime methods are transpiled as a vector of tuples of the form (name, function object).
	//		Given a #method(Q,X,Y1,Z1,Y2,Z2,...,YN,ZN)
	std::array<std::function<void()>, 1> methods = {
		[]() { return add_to_my_int;
		}
	};

	// 3. Runtime calls are transpiled as a vector of tuples of the form (function object index, argument type ids, argument vals as any).
	//		Given a #call(X,Y1,Y2,...,YN)
		//				return std::tuple<X, Y1, Y2, ..., YN>
	std::vector<std::tuple<int, std::vector<std::type_index>, std::vector<std::any>>> start_calls = {
		std::make_tuple(0, std::vector<std::type_index>{typeid(int)}, std::vector<std::any>{my_int})

	};

	auto enter() {
		for (auto& call : enter_calls) {
			call();
		}
	}

	class Main : candil_language::Program {

		




		auto enter() {
			for (auto& call : enter_calls) {
				call();
			}
		}


	};
}
 