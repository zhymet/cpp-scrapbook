#include <cassert>
#include <string>
#include <type_traits>
#include <any>
#include <utility>
#include <functional>
#include <tuple>
#pragma once
#include <unordered_map>
#include <any>
#include <variant>


#pragma once
// Function template for printing a compile-time value
template <typename ValT>
consteval void printCompileTimeValue(const ValT& Value) {
    // This line will be printed at compile time
    std::cout << Value << std::endl;
}

template <typename ExprT>
constexpr void peformCompileTimeConstexpr(ExprT&& expr) {
    expr();
}
// We will transpile the ast to C++ code
// Sample code:
/*
#enter{
    #type(int,&int);
    #vari(a,int); // Variable of type int
    #vari(b@); // variable of type auto

    #method(add,#type(int),{lhs,rhs},{#type(int),#type(int)}); // Method of type int, with 2 int parameters

    #call(add,1,2); // Call method add with 2 parameters ERROR, cant call method returning int into void

    #vari(c@#call(add,1,2)); // ERROR, method body not defined

    // Able to give body to method at a later point.
    #method(add)(
        #return(lhs+rhs);
    );

    #vari(c@#call(add,1,2)); // OK, returns 3, type is the common type of lhs and rhs, which is int

    #class(car)(
        #vari(speed,int);
        #static#const#vari(max_speed,int,100);

        #static#method(get_max_speed@)(#return(max_speed);); // @ is the auto type, deduced from the return type which will be a const int
                                                             // You could also return a #ref(max_speed) but it is not necessary for literal values. const int ref

        #method(speed_up)(
            #if(speed<max_speed)(
                #return(#ref(speed++))
            );

            #return(#ref(speed));
        );

        #method(turbo)(
           #while(speed<max_speed)(
            // When using call not in a variable definition and you wish to send the result to a variable
            // you must use the #into keyword, a special operator which tells the compiler to store the result in a memory location
            // whitespace is not necessary, but is used for readability
            // &self is a special keyword which is a pointer to the current most inner scope object, this being the return value of the speed_up method
            // which is a reference to the member variable speed, in case of pushing a reference into itself is the same as returning void.
            #call(speed_up) #into &self;
        );
    ) #type(car,#class(car));

    #vari(my_car,#type(car));

    #call(my_car,speed_up); // ERROR, cant return #ref(#type(int)) into void.
    #vari(curr_speed@#call(my_car,speed_up)); // OK, when first argument to #call is a non method variable,
                                              // it is assumed to be the this pointer of a member method
    // Sample of using a static method.
    #vari(max_speed@#call(#type(car),get_max_speed)); // OK, returns 100
    #vari(max_speed@#call(#class(car),get_max_speed)); // Use a direct #class object call instead of a #type identity, same meaning (unless type car has other types)
    //#vari(max_speed@#call(my_car,get_max_speed)); // ERROR, cant call static method on non static object

    #print(curr_speed == max_speed); // Prints true because we used turbo to go to max speed.

}
#start{
}
*/

// Viper Program Structure for (AST) and transpilation to C++ code
// 1. All the viper code is wrapped in a namespace called viper
// 2. All the viper standard library code is wrapped in a namespace called vsl (viper standard library)
// 4. All global typdefs are defines. All global variables are defines. All global methods are defines. All global classes are defines.
// 5. Inside a class^
template <char ...Chars>
struct type_string_t {
    static constexpr const char size = { sizeof...(Chars) };
    static constexpr const char data[sizeof...(Chars)] = { Chars... };
};

template <char s(std::size_t), std::size_t ...I>
consteval auto type_string_impl(std::index_sequence<I...>) {
    return type_string_t<s(I)...>();
}

#define type_string(s) decltype(type_string_impl<[](size_t i) {return s[i];}> (std::make_index_sequence<sizeof(s)-1>{}))

namespace cil {
    template<typename T = void>
    struct vari {
        std::any value_ptr_{};
        constexpr auto& ref() {
            return std::any_cast<T&>(value_ptr_);
        }

        constexpr const auto& ref() const {
            return std::any_cast<const T&>(value_ptr_);
        }

        vari() {
            value_ptr_ = std::any(T{});
        }

        vari(T value) {
            value_ptr_ = std::any(value);
        }
    };

    template<>
    struct vari<void> {
        std::any value_ptr_{};
    };

    enum class StatementKind {
        invalid_,				// An invalid statement is a statement that is not a valid statement.
        none_,					// A none statement is a statement that is not a statement.
        statement_,				// A statement is a single line of code.	
        expression_,			// An expression is a statement that returns a value.
        declaration_,			// A declaration is a statement that does not return a value.
        program_,				// A program is a collection of statements.
        compiled_program_,		// A compiled program is all the statemend within the #enter block.
        interpreted_program_,   // An interpreted program is all statement within the #start block.

        // Declarations
        method_declaration_,	// A method declaration creates a method identifier and signature. (not necesseraliy a definition)
        variable_declaration_,	// A variable declaration creates a variable identifier and type. (not necessarily a definition)

        // Directives
        type_directive_,		// A type directive is a declaration that defines a type.
        vari_directive_,		// A vari directive is a declaration that defines a variable.
        type_expression_,		// Returns a type.
        identifier_expression_,	// Returns an identifier.
        value_expression_,		// Returns a value. Which may be one of variable or literal expression.
        variable_expression_,	// Returns a variable which cannot be determined at compile time.
        literal_expression_,	// Returns a literal value. Always determined at compile time.

        // Literals
        literal_value_,			// A literal value is a declaration that defines a literal value.
        integer_literal_,		// An integer literal is a declaration that defines an integer literal value.
        real_literal_,			// A float literal is a declaration that defines a float literal value.
        string_literal_,		// A string literal is a declaration that defines a string literal value.
        alnumus_literal_,		// An alnumus literal is a declaration that defines an alnumus literal value.
        type_literal_,			// A type literal is a declaration that defines a type literal value.
        variable_definition_,	// A variable definition is a declaration that defines a variable.
        method_definition_,		// A method definition is a declaration that defines a method.

        // EOF
        eof_,
    };



    using ViperAstNode = std::variant<>;


    struct Statement {
        using statement_list = std::list<Statement>;

        StatementKind kind;								    // Type of statement.
        statement_list body;								// Body of the statement which recursively contains statements.
        std::string literal; 							    // Literal text of the statement.
        Statement& parent;								    // Parent statement.
    };

    class ViperTranspiler {
        std::string cpp_code_;
        Statement viper_ast_;

        std::string transpile_invalid_statement(const Statement& statement) {
            std::string cpp_statement = "/* Invalid Statement */ static_assert<false && \"[CRITICAL_ERROR][INVALID STATEMENT IN VIPER CODE]\">;";
            return cpp_statement;
        }

        std::string transpile_type_directive_statement(const Statement& statement) {
            std::string cpp_statement = "";

            // If the type directive statement has a body of size 1, then its a type declaration.
            // If the type directive statement has a body of size 2, then its a type definition.

            if (statement.body.size() == 1) {
                // Type declaration
                // #type(<identity_expression>);

                // Get the identity expression
                auto identity_expression = statement.body.front();

                // Solve the identity expresssion (for now we will simply allow 1 alnumus token)
                // Assert size of identity is 1 and contains a literal identity
                assert((identity_expression.body.size() == 1)
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain a single statement.]");
                assert((identity_expression.body.front().kind == StatementKind::alnumus_literal_)
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain alnumus_literal]");

                // Get the literal identity
                auto identity = identity_expression.body.front().literal;

                // Look up the type identity in the type map
                auto type = viper_type_map_.find(identity);

                // Assert that the type identity exists in the type map
                assert((type != viper_type_map_.end())
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type identity not found in type map]");

                // Get the underlying C++ type from the type map
                auto cpp_type = type->second;

                // Create the C++ statement
                // #type(<identity_expression>);
                // becomes
                // vari<cpp_type>

                cpp_statement = "vari<" + cpp_type + ">";
            }
            else if (statement.body.size() == 2) {
                // Type definition
                // #type(<identity_expression>,<type_expression>);
                // Get the identity expression
                auto identity_expression = statement.body.front();

                // Solve the identity expresssion (for now we will simply allow 1 alnumus token)
                // Assert size of identity is 1 and contains a literal identity
                assert((identity_expression.body.size() == 1)
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain a single statement.]");
                assert((identity_expression.body.front().kind == StatementKind::alnumus_literal_)
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain alnumus_literal]");

                // Get the literal identity
                auto identity = identity_expression.body.front().literal;

                // Look up the type identity in the type map

                auto type = viper_type_map_.find(identity);

                // Assert that the type identity does not exists in the type map
                assert((type == viper_type_map_.end())
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type identity already exists in type map]");
                // Get the type expression
                auto type_expression = statement.body.back();

                // Solve the type expression
                // for now we will only allow 1 type declaration or 1 literal type
                // Assert size of type expression is 1 and contains a type declaration or literal type
                assert((type_expression.body.size() == 1)
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain a single statement.]");
                assert(((type_expression.body.front().kind == StatementKind::type_directive_) || (type_expression.body.front().kind == StatementKind::type_literal_))
                    && "[TRANSPILER][ERROR][transpile_type_directive_statement][Type declaration must contain type_directive or type_literal]");

                // Get the type
                std::string cpp_type;
                if (type_expression.body.front().kind == StatementKind::type_directive_) {
                    // If the type expression contains a type directive, then we must solve the type directive by calling this method recursiveley
                    cpp_type = transpile_type_directive_statement(type_expression.body.front());
                }
                else if (type_expression.body.front().kind == StatementKind::type_literal_) {
                    // If the type expression contains a literal_type, then we must get the literal_type and use it as the C++ type
                    cpp_type = type_expression.body.front().literal;
                }

                // Add the type identity and C++ type to the type map
                viper_type_map_.insert({ identity, cpp_type });

                // Create the C++ statement
                // #type(<identity_expression>,<type_expression>);
                // becomes
                // using <identity_expression>_t = <type_expression>;

                cpp_statement = "using " + identity + "_t = " + cpp_type + ";";
            }

            return cpp_statement;
        }

        auto transpile_statement(const Statement& statement) {
            switch (statement.kind) {
                //case StatementKind::invalid_:
                //	return transpile_invalid_statement(statement);
                //case StatementKind::none_:
                //	return transpile_none_statement(statement);
                //case StatementKind::statement_:
                //	return transpile_statement_statement(statement);
                //case StatementKind::expression_:
                //	return transpile_expression_statement(statement);
                //case StatementKind::declaration_:
                //	return transpile_declaration_statement(statement);
                //case StatementKind::program_:
                //	return transpile_program_statement(statement);
                //case StatementKind::compiled_program_:
                //	return transpile_compiled_program_statement(statement);
                //case StatementKind::interpreted_program_:
                //	return transpile_interpreted_program_statement(statement);
                //case StatementKind::method_declaration_:
                //	return transpile_method_declaration_statement(statement);
                //case StatementKind::variable_declaration_:
                //	return transpile_variable_declaration_statement(statement);
            case StatementKind::type_directive_:
                return transpile_type_directive_statement(statement);
                //case StatementKind::vari_directive_:
                //	return transpile_vari_directive_statement(statement);
                //case StatementKind::type_expression_:
                //	return transpile_type_expression_statement(statement);
                //case StatementKind::identifier_expression_:
                //	return transpile_identifier_expression_statement(statement);
                //case StatementKind::value_expression_:
                //	return transpile_value_expression_statement(statement);
                //case StatementKind::variable_expression_:
                //	return transpile_variable_expression_statement(statement);
                //case StatementKind::literal_expression_:
                //	return transpile_literal_expression_statement(statement);
                //case StatementKind::literal_value_:
                //	return transpile_literal_value_statement(statement);
                //case StatementKind::integer_literal_:
                //	return transpile_integer_literal_statement(statement);
                //case StatementKind::real_literal_:
                //	return transpile_real_literal_statement(statement);
                //case StatementKind::string_literal_:
                //	return transpile_string_literal_statement(statement);
                //case StatementKind::variable_definition_:
                //	return transpile_variable_definition_statement(statement);
                //case StatementKind::method_definition_:
                //	return transpile_method_definition_statement(statement);
                //case StatementKind::eof_:
                //	return transpile_eof_statement(statement);
            default:
                return transpile_invalid_statement(statement);
            }
        }

    };
}

namespace vip {
    template<typename T = void>
    struct vari {
        std::any value_ptr_{};
        constexpr auto& ref() {
            return std::any_cast<T&>(value_ptr_);
        }

        constexpr const auto& ref() const {
            return std::any_cast<const T&>(value_ptr_);
        }

        vari() {
            value_ptr_ = std::any(T{});
        }

        vari(T value) {
            value_ptr_ = std::any(value);
        }
    };

    template<>
    struct vari<void> {
        std::any value_ptr_{};
    };

    struct viper_program {
        using int_t = int;

        static vari<int_t> add(vari<int_t> lhs, vari<int_t> rhs) {
            return (lhs.ref() + rhs.ref());
        }

        vari<int_t> a; // int type
        vari<void> b;                 // auto type
        vari<int_t> c = add(1, 2);

        class car {
        public: // Everything is public by default
            vari<int_t> speed;
            static const vari<int_t> max_speed; // according to C++ standard, static const variables must be defined outside of the class
            // so we will define below.

            static vari<int_t> get_max_speed() {
                return max_speed;
            }

            vari<int_t>& speed_up() {
                if (speed.ref() < max_speed.ref()) {
                    speed.ref()++;
                }
                return speed;
            }

            constexpr void turbo() {
                while (speed.ref() < max_speed.ref()) {
                    speed_up(); // #into &self taking effect here
                }
            }
        };

        // defining my car
        using viper_type_car = car; // car registered as a type

        vari<viper_type_car> my_car;

        vari<int_t> curr_speed = my_car.ref().speed_up();


        vari<int_t> max_speed = car::get_max_speed(); // static method call
    };
    const vari<viper_program::int_t> viper_program::car::max_speed = 100;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Viper Runtime
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto viper_runtime() {
        viper_program program;

        std::cout << "vip::a value:" << program.a.ref() << std::endl;

        vari<viper_program::int_t> curr_speed = program.my_car.ref().speed_up();
        program.my_car.ref().turbo();

        // print current speed of the car 
        printCompileTimeValue(program.my_car.ref().speed.ref());

        // print curr_speed == max_speed
        printCompileTimeValue(program.my_car.ref().speed.ref() == viper_program::car::max_speed.ref());

        return program;
    }
}

