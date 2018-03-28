#include <string>
#include <map>
#include <fstream>
#include "../Token.cpp"
#include "Lexer.h"

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
};

char Lexer::NextChar()
{
    this->currentChar = inputString->at(this->currentPosition);
    this->currentPosition++;
    return this->currentChar;
}