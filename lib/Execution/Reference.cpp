#include <stack>
#include <map>
#include <string>
#include "../Token.h"
#include "Reference.h"

using namespace std;

Reference::Reference()
{
    this->scopes = new stack<map<string, ASTNode *> *>();
    this->push();
}

void Reference::push()
{
    this->scopes->push(new map<string, ASTNode *>());
}

void Reference::insert(Token *identifier, ASTNode *node)
{
    this->scopes->top()->insert(pair<string, ASTNode*>(*(identifier->value), node));
}

ASTNode *Reference::lookup(Token *identifier)
{
    stack<map<string, ASTNode*> *> dump = *(this->scopes);

    while(!dump.empty())
    {
        try
        {
            return dump.top()->at(*(identifier->value));
        }
        catch(const out_of_range &e)
        {
            dump.pop();
        }
    }

    return NULL;
}

void Reference::pop()
{
    this->scopes->pop();
}

map<string, ASTNode*> *Reference::currentScope()
{
    return this->scopes->top();
}