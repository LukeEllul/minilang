set (CMAKE_CXX_STANDARD 11)

project("minilang")

add_executable(repl 
                    ./lib/Lexer/Lexer.cpp
                    ./lib/Parser/ASTNodes.cpp
                    ./lib/Parser/Parser.cpp
                    ./lib/Execution/Interpreter.cpp
                    ./lib/Execution/Reference.cpp
                    ./lib/SemanticAnalyzer/SemanticAnalyzer.cpp
                    ./lib/SemanticAnalyzer/SymbolTable.cpp
                    ./lib/REPL/REPL.cpp
                    ./lib/repl.cpp
                    )

add_executable(minilang 
                    ./lib/Lexer/Lexer.cpp
                    ./lib/Parser/ASTNodes.cpp
                    ./lib/Parser/Parser.cpp
                    ./lib/Execution/Interpreter.cpp
                    ./lib/Execution/Reference.cpp
                    ./lib/SemanticAnalyzer/SemanticAnalyzer.cpp
                    ./lib/SemanticAnalyzer/SymbolTable.cpp
                    ./lib/REPL/REPL.cpp
                    ./lib/main.cpp
                    )