#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stack>
#include "../Token.h"
#include "Lexer.h"

#include "ClassifierTable.h"
#include "TokenTypeTable.h"
#include "TransitionTable.h"

using namespace std;

Lexer::Lexer(const char *fileName)
{
    string *inputString = new string();

    char c;
    fstream fin(fileName, fstream::in);
    while (fin.get(c))
    {
        *inputString += c;
    }

    this->inputString = inputString;
    this->currentPosition = 0;
    this->end = 0;

    this->ClassifierTable = ClassifierTableX;
    this->TokenTypeTable = TokenTypeTableX;
    this->TransitionTable = TransitionTableX;
};

char Lexer::NextChar()
{
    if (this->currentPosition == inputString->length())
    {
        if (this->end == 0)
            this->end = 1;
        return EOF;
    }

    this->currentChar = inputString->at(this->currentPosition);
    this->currentPosition++;
    return this->currentChar;
}

Token *Lexer::NextToken()
{
    TokenType state = (TokenType)(-1);
    string *lexeme = new string();

    stack<TokenType> *states = new stack<TokenType>();
    states->push((TokenType)BAD);

    while (state != INVALID)
    {
        char ch = this->NextChar();
        *lexeme += ch;

        if (finalStates[state] == state)
        {
            states->empty();
        }

        states->push((TokenType)state);
        try
        {
            TokenType cat = ClassifierTable->at(ch);
            state = TransitionTable[state + 1][cat];
        }
        catch (const out_of_range &e)
        {
            state = INVALID;
        }
    }

    // for (stack<TokenType> dump = *states; !dump.empty(); dump.pop())
    //     cout << dump.top() << endl;

    //cout << finalStates[32] << endl;

    while ((finalStates[state] != state || finalStates[state] == INVALID) && state != BAD)
    {
        state = states->top();
        states->pop();
        lexeme->pop_back();
        this->currentPosition--;
    }

    if (finalStates[state] == state)
    {
        Token *token = new Token();

        if (this->end == 2)
        {
            token->type = (TokenType)TOK_EOF;
            token->value = NULL;
            return token;
        }

        if (this->end == 1)
        {
            this->end = 2;
        }

        //TODO handle keywords here by checking lexeme

        token->type = state;
        token->value = lexeme;

        return token;
    }
    else
    {
        Token *token = new Token();
        token->type = (TokenType)INVALID;
        token->value = NULL;

        return token;
    }
}