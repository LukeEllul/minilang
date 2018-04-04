#include <string>

using namespace std;

enum TokenType {
    TOK_Number,
    TOK_ArithmeticOP,
    TOK_BOOLEAN,
    TOK_ALPHA_SMALL,
    TOK_ALPHA_LARGE,
    TOK_PUNC,
    TOK_EOF
};

typedef struct 
{
    char const *name;
    TokenType type;
    int location[2];
    string *value;
} Token;