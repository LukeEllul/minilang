#include <stack>
#include <map>
#include <string>
#include "../Token.h"
#include "Reference.h"

using namespace std;

Reference::Reference()
{
    this->scopes = new stack<map<string, string *> *>();
    this->push();
}

void Reference::push()
{
    this->scopes->push(new map<string, string *>());
}

void Reference::insert(Token *identifier, string *s)
{
    this->scopes->top()->insert(pair<string, string*>(*(identifier->value), s));
}

void Reference::update(Token *identifier, string *s)
{
    stack<map<string, string*> *> dump = *(this->scopes);

    while(!dump.empty())
    {
        try
        {
            dump.top()->at(*(identifier->value));
            (*(dump.top()))[*(identifier->value)] = s;
            return;
        }
        catch(const out_of_range &e)
        {
            dump.pop();
        }
    }
}

string *Reference::lookup(Token *identifier)
{
    stack<map<string, string*> *> dump = *(this->scopes);

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

map<string, string*> *Reference::currentScope()
{
    return this->scopes->top();
}