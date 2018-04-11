#ifndef TRANSITION_TABLE
#define TRANSITION_TABLE
#include "../Token.h"

const TokenType TransitionTable[][17] = {
    /*START TODO*/ {(TokenType)LETTER, (TokenType)INTEGER_LITERAL, (TokenType)INVALID, (TokenType)MULTIPLICATIVE_OP, (TokenType)ADDITIVE_OP, (TokenType)RELATIONAL_OP, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)RELATIONAL_OP, (TokenType)IDENTIFIER, (TokenType)RELATIONAL_OP, (TokenType)STRING_LITERAL, (TokenType)INVALID},

    /*LETTER*/ {(TokenType)LETTER, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*DIGIT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*PRINTABLE*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*RELATIONAL_OP*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*INTEGER_LITERAL*/ {(TokenType)INVALID, (TokenType)INTEGER_LITERAL, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)REAL_LITERAL, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*REAL_LITERAL*/ {(TokenType)INVALID, (TokenType)REAL_LITERAL, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*STRING_LITERAL*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)STRING_LITERAL, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)LITERAL, (TokenType)INVALID},

    /*LITERAL*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},

    /*IDENTIFIER*/ {(TokenType)IDENTIFIER, (TokenType)IDENTIFIER, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)IDENTIFIER, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID}

    // /*SUB_EXPRESSION*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*UNARY*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*FACTOR*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*TERM*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*SIMPLE_EXPRESSION*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*EXPRESSION*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*ASSIGNMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*VARIABLE_DECL*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*PRINT_STATEMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*RETURN_STATEMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*IF_STATEMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*WHILE_STATEMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*FORMAL_PARAM*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*FORMAL_PARAMS*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*FUNCTION_DECL*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*STATEMENT*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*BLOCK*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
    // /*PROGRAM*/ {(TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID, (TokenType)INVALID},
};

const TokenType (*TransitionTableX)[17] = TransitionTable;

#endif