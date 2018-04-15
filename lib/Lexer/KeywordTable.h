#ifndef KEYWORD_TABLE
#define KEYWORD_TABLE
#include <map>
#include <string.h>
#include "../Token.h"

using namespace std;

struct compareString
{
    bool operator()(char const *a, char const *b)
    {   
        return strcmp(a, b) < 0;
    }
};

map<const char*, TokenType, compareString> *KeywordTable = new map<const char*, TokenType, compareString>(
    {
        {"and", (TokenType)MULTIPLICATIVE_OP},
        {"or", (TokenType)ADDITIVE_OP},

        {"real", (TokenType)TYPE},
        {"int", (TokenType)TYPE},
        {"bool", (TokenType)TYPE},
        {"string", (TokenType)TYPE},

        {"true", (TokenType)BOOLEAN_LITERAL},
        {"false", (TokenType)BOOLEAN_LITERAL},

        {"set", (TokenType)SET},

        {"var", (TokenType)VAR},

        {"print", (TokenType)PRINT},

        {"return", (TokenType)RETURN},

        {"if", (TokenType)IF},
        {"else", (TokenType)ELSE},

        {"while", (TokenType)WHILE},

        {"def", (TokenType)DEF}
    }
);

#endif