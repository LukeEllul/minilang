#include <iostream>
#include <stack>
#include <string>
#include <string.h>
#include <sstream>
#include "../Token.h"
#include "../SemanticAnalyzer/SymbolTable.h"
#include "../Parser/ASTNodes.h"
#include "Reference.h"
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(ASTNode *program)
{
    this->rf = new Reference();
}

string *Interpreter::InterpretFactor(ASTNode *factor)
{
    stack<ASTNode *> dump = *(factor->getNodes());
    ASTNode *node = dump.top();

    if(node->getToken()->type == LITERAL)
    {
        node = node->getNodes()->top();

        if(node->getToken()->type == STRING_LITERAL)
        {
            stack<ASTNode *> dump = *(node->getNodes());
            dump.pop();
            return dump.top()->getToken()->value;
        }

        return node->getToken()->value;
    }
    if(node->getToken()->type == IDENTIFIER)
    {
        return rf->lookup(node->getToken());
    }
    if(node->getToken()->type == FUNCTION_CALL)
    {
        stack<ASTNode *> dump = *(node->getNodes());
        dump.pop();
        dump.pop();
        dump.pop();
        ASTNode *identifier = dump.top();
        
        //TODO
    }
    if(node->getToken()->type == SUB_EXPRESSION)
    {
        stack<ASTNode *> dump = *(node->getNodes());
        dump.pop();
        ASTNode *expression = dump.top();

        return InterpretExpression(expression);
    }
    if(node->getToken()->type == UNARY)
    {
        stack<ASTNode *> dump = *(node->getNodes());
        ASTNode *expression = dump.top();
        string *e = InterpretExpression(expression);
        return &(new string("-")->append(*e));
    }
}

string *Interpreter::InterpretTerm(ASTNode *term)
{
    stack<ASTNode *> dump = *(term->getNodes());
    ASTNode *factor = dump.top();
    dump.pop();
    string *e = InterpretFactor(factor);

    while(!dump.empty())
    {
        dump.pop();
        string *n = InterpretFactor(dump.top());
        double n1 = stod(*e);
        double n2 = stod(*n);

        ostringstream strs;
        strs << (n1 * n2);
        e = &(strs.str());
        
        dump.pop();
    }

    return e;
}

string *Interpreter::InterpretSimpleExpression(ASTNode *simpleExpression)
{
    stack<ASTNode *> dump = *(simpleExpression->getNodes());
    ASTNode *term = dump.top();
    dump.pop();
    string *e = InterpretTerm(term);

    while(!dump.empty())
    {
        dump.pop();
        string *n = InterpretTerm(dump.top());
        double n1 = stod(*e);
        double n2 = stod(*n);

        ostringstream strs;
        strs << (n1 + n2);
        e = &(strs.str());

        dump.pop();
    }

    return e;
}

string *Interpreter::InterpretExpression(ASTNode *expression)
{
    stack<ASTNode *> dump = *(expression->getNodes());
    ASTNode *simpleExpression = dump.top();
    dump.pop();
    string *e = InterpretSimpleExpression(simpleExpression);

    while(!dump.empty())
    {
        ASTNode *relationalOp = dump.top();
        const char *v = relationalOp->getToken()->value->c_str();
        dump.pop();
        string *n = InterpretSimpleExpression(dump.top());

        if(strcmp(v, "<") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if(n2 < n1) e = new string("true");
            else e = new string("false");
        }
        if(strcmp(v, ">") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if(n2 > n1) e = new string("true");
            else e = new string("false");
        }
        if(strcmp(v, "<=") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if(n2 <= n1) e = new string("true");
            else e = new string("false");
        }
        if(strcmp(v, ">=") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if(n2 >= n1) e = new string("true");
            else e = new string("false");
        }

        const char *E = e->c_str();
        const char *N = n->c_str();

        if(strcmp(v, "==") == 0)
        {
            if(strcmp(E, N) == 0) e = new string("true");
            else e = new string("false");
        }
        if(strcmp(v, "!=") == 0)
        {
            if(strcmp(E, N) == 0) e = new string("false");
            else e = new string("true");
        }

        dump.pop();
    }

    return e;
}

void Interpreter::InterpretAssignment(ASTNode *assignment)
{
    stack<ASTNode *> dump = *(assignment->getNodes());
    string *e = InterpretExpression(dump.top());
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();
    
    rf->insert(identifier->getToken(), e);
}

void Interpreter::InterpretVariableDecl(ASTNode *variableDec)
{
    stack<ASTNode *> dump = *(variableDec->getNodes());
    string *e = InterpretExpression(dump.top());
    dump.pop();
    dump.pop();
    dump.pop();
    dump.pop();
    
    ASTNode *identifier = dump.top();

    rf->insert(identifier->getToken(), e);
}

void Interpreter::InterpretPrintStatement(ASTNode *printStatement)
{
    stack<ASTNode *> dump = *(printStatement->getNodes());
    string *e = InterpretExpression(dump.top());

    cout << *e << endl;
}

string *Interpreter::InterpretReturnStatement(ASTNode *returnStatement)
{
    stack<ASTNode *> dump = *(returnStatement->getNodes());

    return InterpretExpression(dump.top());
}