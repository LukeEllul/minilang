#include <string>

using namespace std;

enum TokenType {
    LETTER,
    DIGIT,
    PRINTABLE,
    TYPE,
    BOOLEAN_LITERAL,
    INTEGER_LITERAL,
    REAL_LITERAL,
    STRING_LITERAL,
    LITERAL,
    IDENTIFIER,
    MULTIPLICATIVE_OP,
    ADDITIVE_OP,
    RELATIONAL_OP,
    ACTUAL_PARAMS,
    FUNCTION_CALL,
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

typedef struct 
{
    char const *name;
    TokenType type;
    int location[2];
    string *value;
} Token;