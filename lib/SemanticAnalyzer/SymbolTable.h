#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stack>
#include <map>
#include <string>
#include "../Token.h"

using namespace std;

class SymbolTable
{
  private:
    stack<map<string, TokenType> *> *scopes;

  public:
    SymbolTable();
    void push();
    void insert(Token *identifier, TokenType type);
    TokenType lookup(Token *identifier);
    void pop();
    map<string, TokenType> *currentScope();
};

#endif