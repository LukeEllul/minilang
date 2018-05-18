#include <stack>
#include <map>
#include <string>
#include "../Token.h"
#include "./SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable()
{
    this->scopes = new stack<map<string, TokenType> *>();
    this->push();
}

void SymbolTable::push()
{
    this->scopes->push(new map<string, TokenType>());
}

void SymbolTable::insert(Token *identifier, TokenType type)
{
    this->scopes->top()->insert(pair<string, TokenType>(*(identifier->value), type));
}

void SymbolTable::update(Token *identifier, TokenType type)
{
    stack<map<string, TokenType> *> dump = *(this->scopes);

    while (!dump.empty())
    {
        try
        {
            dump.top()->at(*(identifier->value));
            (*(dump.top()))[*(identifier->value)] = type;
            return;
        }
        catch (const out_of_range &e)
        {
            dump.pop();
        }
    }
}

TokenType SymbolTable::lookup(Token *identifier)
{
    stack<map<string, TokenType> *> dump = *(this->scopes);

    while (!dump.empty())
    {
        try
        {
            return dump.top()->at(*(identifier->value));
        }
        catch (const out_of_range &e)
        {
            dump.pop();
        }
    }

    return INVALID;
}

void SymbolTable::pop()
{
    this->scopes->pop();
}

map<string, TokenType> *SymbolTable::currentScope()
{
    return this->scopes->top();
}