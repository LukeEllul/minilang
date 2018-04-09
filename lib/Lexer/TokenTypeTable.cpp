#include <iostream>
#include "../Token.cpp"

//states
TokenType const TokenTypeTable[] = {
    LETTER,
    DIGIT,
    PRINTABLE,
    RELATIONAL_OP,
    INTEGER_LITERAL,
    REAL_LITERAL,
    STRING_LITERAL,
    LITERAL,
    IDENTIFIER,

    //transition table conmments start here
    SUB_EXPRESSION,
    UNARY,
    FACTOR,
    TERM,
    SIMPLE_EXPRESSION,
    EXPRESSION,
    ASSIGNMENT,
    VARIABLE_DECL,
    PRINT_STATEMENT,
    RETURN_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FORMAL_PARAM,
    FORMAL_PARAMS,
    FUNCTION_DECL,
    STATEMENT,
    BLOCK,
    PROGRAM
};