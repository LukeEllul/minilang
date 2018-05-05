#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stack>
#include <map>
#include <string>
#include "../Token.h"
#include "../Parser/ASTNodes.h"

using namespace std;

class SymbolTable
{
  private:
    stack<map<string, TokenType> *> *scopes;
    ASTNode *tree;

  public:
    SymbolTable(ASTNode *program);
    void push();
    void insert(Token *identifier, TokenType type);
    TokenType lookup(Token *identifier);
    void pop();
};

#endif