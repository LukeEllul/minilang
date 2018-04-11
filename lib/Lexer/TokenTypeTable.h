#ifndef TOKEN_TABLE
#define TOKEN_TABLE
#include <iostream>
#include "../Token.h"

using namespace std;

//states
const TokenType TokenTypeTableXX[] = {
    (TokenType)LETTER,
    (TokenType)DIGIT,
    (TokenType)PRINTABLE,
    (TokenType)MULTIPLICATIVE_OP,
    (TokenType)ADDITIVE_OP,
    (TokenType)RELATIONAL_OP,
    (TokenType)LEFT_BRACKET,
    (TokenType)RIGHT_BRACKET,
    (TokenType)COLON,
    (TokenType)SEMI_COLON,
    (TokenType)PERIOD,
    (TokenType)COMMA,
    (TokenType)EQUALS,
    (TokenType)UNDERSCORE,
    (TokenType)EXCLAMATION_MARK,
    (TokenType)INVERTED_COMMA,
    (TokenType)TOK_EOF,
    (TokenType)TYPE,
    (TokenType)BOOLEAN_LITERAL,
    (TokenType)INTEGER_LITERAL,
    (TokenType)REAL_LITERAL,
    (TokenType)STRING_LITERAL,
    (TokenType)LITERAL,
    (TokenType)IDENTIFIER,

    //transition table conmments start here
    (TokenType)SUB_EXPRESSION,
    (TokenType)UNARY,
    (TokenType)FACTOR,
    (TokenType)TERM,
    (TokenType)SIMPLE_EXPRESSION,
    (TokenType)EXPRESSION,
    (TokenType)ASSIGNMENT,
    (TokenType)VARIABLE_DECL,
    (TokenType)PRINT_STATEMENT,
    (TokenType)RETURN_STATEMENT,
    (TokenType)IF_STATEMENT,
    (TokenType)WHILE_STATEMENT,
    (TokenType)FORMAL_PARAM,
    (TokenType)FORMAL_PARAMS,
    (TokenType)FUNCTION_DECL,
    (TokenType)STATEMENT,
    (TokenType)BLOCK,
    (TokenType)PROGRAM
};

const TokenType *TokenTypeTableX = TokenTypeTableXX;

//final states
TokenType const finalStatesX[] = {
    (TokenType)LETTER,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)MULTIPLICATIVE_OP,
    (TokenType)ADDITIVE_OP,
    (TokenType)RELATIONAL_OP,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)NULL,
    (TokenType)INTEGER_LITERAL,
    (TokenType)REAL_LITERAL,
    (TokenType)STRING_LITERAL,
    (TokenType)LITERAL,
    (TokenType)IDENTIFIER,
};

const TokenType *finalStates = finalStatesX;

#endif