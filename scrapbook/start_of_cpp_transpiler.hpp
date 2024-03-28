#pragma once
#include <string>
#include "any_type_ptr.hpp"
#include "ast_node.hpp"
namespace caoco {
    class Transpiler {
        std::string cpp_code_;
        
        std::string transpile_invalid_statement(const Node& statement) {
            std::string cpp_statement = "/* Invalid Statement */ static_assert(false && \"[CRITICAL_ERROR][INVALID STATEMENT IN C& CODE]\");";
            return cpp_statement;
        }
        
        // Anon Var Def
        // #var <name>;
        std::string transpile_anon_var_def(const Node& statement) {
            assert(statement.type() == Node::eType::anon_variable_definition_
            && "[TranspilerLogicalError] Statement Passed to TranspileAnonVarDef must be of type anon_var_def.");
            
            assert(statement.body().size() == 1 && "[TranspilerLogicalError] Statement Passed to TranspileAnonVarDef must have 1 child.");

            std::string cpp_statement = "auto " + to_std_string(statement.body().front().to_string()) + " = csl::AnyTypePtr();";

            return cpp_statement;
        }

        // Identifier Statement
        // #var <name> = <value>;
        std::string transpile_identifier_statement(const Node& statement) {
			assert(statement.type() == Node::eType::variable_assignment_
            			&& "[TranspilerLogicalError] Statement Passed to TranspileIdentifierStatement must be of type identifier_statement.");
			
			assert(statement.body().size() == 3 && "[TranspilerLogicalError] Statement Passed to TranspileIdentifierStatement must have 3 children.");

			std::string cpp_statement = to_std_string(statement.body().front().to_string()) + " = " + to_std_string(statement.body().back().to_string()) + ";";

			return cpp_statement;
		}

    public:
        std::string transpile(const Node& program) {
            // Expecting a pragmatic block
            assert(program.type() == Node::eType::pragmatic_block_ && "[TranspilerLogicalError] Statement Passed to Transpile must be of type pragmatic_block.");
            std::string output = "";
            std::string main_method = "";
            // Add Candil C++ Language Dependencies
            output += "#include \"any_type_ptr.hpp\"\n";

            // Open the candi namespace
            output += "namespace candi {\n";

            // Transpile each statement in the block

            for (const auto& stmt : program.body()) {
                switch (stmt.type()) {
                case Node::eType::variable_assignment_:
                    main_method += transpile_identifier_statement(stmt) + "\n"; break;
                case Node::eType::anon_variable_definition_:
                    output += transpile_anon_var_def(stmt)+"\n"; break;
                default:
					output += transpile_invalid_statement(stmt); break;
                }
            }

            // Add the main method
            main_method = "void enter() {\n" + main_method + "\n}\n";
            output += main_method;
            // Close the candi namespace
            output += "};\n";

            return output;
        }
    };
}