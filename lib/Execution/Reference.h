#ifndef REFERENCE_H
#define REFERENCE_H
#include <stack>
#include <string>
#include <map>
#include "../Token.h"
#include "../Parser/ASTNodes.h"

using namespace std;

class Reference 
{
    private:
        stack<map<string, ASTNode*> *> *scopes;

    public:
        Reference();
        void push();
        void insert(Token *identifier, ASTNode *node);
        ASTNode *lookup(Token *identifier);
        void pop();
        map<string, ASTNode*> *currentScope();
};

#endif