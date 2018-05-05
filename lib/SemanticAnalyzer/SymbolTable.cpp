#include <stack>
#include <map>
#include <string>
#include "../Token.h"
#include "../Parser/ASTNodes.h"
#include "./SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable(ASTNode *program)
{
    this->tree = program;
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

TokenType SymbolTable::lookup(Token *identifier)
{
    try
    {
        return this->scopes->top()->at(*(identifier->value));
    } catch(const out_of_range &e)
    {
        return INVALID;
    }
}

void SymbolTable::pop()
{
    this->scopes->pop();
}