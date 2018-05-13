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
        stack<map<string, string*> *> *scopes;

    public:
        Reference();
        void push();
        void insert(Token *identifier, string *s);
        string *lookup(Token *identifier);
        void pop();
        map<string, string*> *currentScope();
};

#endif