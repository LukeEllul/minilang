#include <string>
#include <map>
#include <fstream>
#include <stack>
#include "../Token.cpp"
#include "Lexer.h"

#include "ClassifierTable.cpp"
#include "TokenTypeTable.cpp"
#include "TransitionTable.cpp"

using namespace std;

Lexer::Lexer(string *fileName)
{
    string *inputString = new string();

    char c;
    fstream fin(fileName->c_str(), fstream::in);
    while(fin.get(c))
    {
        *inputString += c;
    }

    this->inputString = inputString;
    this->currentChar = NULL;
    this->currentPosition = 0;

    this->ClassifierTable = ClassifierTableX;
    this->TokenTypeTable = TokenTypeTableX;
    this->TransitionTable = TransitionTableX;
};

char Lexer::NextChar()
{
    this->currentChar = inputString->at(this->currentPosition);
    this->currentPosition++;
    return this->currentChar;
}

Token *Lexer::NextToken()
{
    TokenType state = (TokenType)NULL;
    string *lexeme = new string();


    stack<TokenType> *states = new stack<TokenType>();
    states->push((TokenType)BAD);

    while(state != INVALID)
    {
        char ch = this->NextChar();
        *lexeme += ch;
    }
}