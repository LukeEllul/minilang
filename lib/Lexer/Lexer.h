#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <map>
#include "../Token.h"

using namespace std;

class Lexer 
{
    private:
        string *inputString;
        char currentChar;
        int currentPosition;
        int end;

        char NextChar();
        map<char,TokenType> *ClassifierTable;
        TokenType const *TokenTypeTable;
        TokenType const (*TransitionTable)[19];

    public:
        Token *NextToken();
        Lexer(const char *filePath);
        ~Lexer();
};

#endif