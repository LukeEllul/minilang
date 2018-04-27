set (CMAKE_CXX_STANDARD 11)

project("minilang")

add_executable(minilang 
                    ./lib/Lexer/Lexer.cpp
                    ./lib/Parser/ASTNodes.cpp
                    ./lib/Parser/Parser.cpp
                    ./lib/main.cpp
                    )