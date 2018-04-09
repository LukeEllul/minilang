#include <string>

using namespace std;

enum TokenType
{
    LETTER,
    DIGIT,
    PRINTABLE,
    MULTIPLICATIVE_OP,
    ADDITIVE_OP,
    RELATIONAL_OP,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COLON,
    SEMI_COLON,
    PERIOD,
    COMMA,
    EQUALS,
    UNDERSCORE,
    EXCLAMATION_MARK,
    INVERTED_COMMA,
    TOK_EOF,
    TYPE,
    BOOLEAN_LITERAL,
    INTEGER_LITERAL,
    REAL_LITERAL,
    STRING_LITERAL,
    LITERAL,
    IDENTIFIER,
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
    PROGRAM,

    INVALID,
};

typedef struct
{
    char const *name;
    TokenType type;
    int location[2];
    string *value;
} Token;