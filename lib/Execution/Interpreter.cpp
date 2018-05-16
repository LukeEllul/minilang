#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <string.h>
#include <sstream>
#include "../Token.h"
#include "../SemanticAnalyzer/SymbolTable.h"
#include "../Parser/ASTNodes.h"
#include "Reference.h"
#include "Interpreter.h"

using namespace std;

void printThisStack(stack<ASTNode *> *s)
{
    for (stack<ASTNode *> dump = *s; !dump.empty(); dump.pop())
        cout << *(dump.top()->getToken()->value) << endl;
}

Interpreter::Interpreter(ASTNode *program)
{
    this->rf = new Reference();
    this->functionDefs = new map<string, ASTNode *>();
}

string *Interpreter::InterpretFactor(ASTNode *factor)
{
    stack<ASTNode *> dump = *(factor->getNodes());
    ASTNode *node = dump.top();

    if (node->getToken()->type == LITERAL)
    {
        node = node->getNodes()->top();

        if (node->getToken()->type == STRING_LITERAL)
        {
            stack<ASTNode *> dump = *(node->getNodes());
            dump.pop();
            return dump.top()->getToken()->value;
        }

        return node->getToken()->value;
    }
    if (node->getToken()->type == IDENTIFIER)
    {
        return rf->lookup(node->getToken());
    }
    if (node->getToken()->type == FUNCTION_CALL)
    {
        return InterpretFunctionCall(node);
    }
    if (node->getToken()->type == SUB_EXPRESSION)
    {
        stack<ASTNode *> dump = *(node->getNodes());
        dump.pop();
        ASTNode *expression = dump.top();

        return InterpretExpression(expression);
    }
    if (node->getToken()->type == UNARY)
    {
        stack<ASTNode *> dump = *(node->getNodes());
        ASTNode *expression = dump.top();
        string *e = InterpretExpression(expression);
        return &((new string("-"))->append(*e));
    }
}

string *Interpreter::InterpretTerm(ASTNode *term)
{
    stack<ASTNode *> dump = *(term->getNodes());
    ASTNode *factor = dump.top();
    dump.pop();
    string *e = InterpretFactor(factor);

    while (!dump.empty())
    {
        dump.pop();
        string *n = InterpretFactor(dump.top());
        double n1 = stod(*e);
        double n2 = stod(*n);

        ostringstream strs;
        strs << (n1 * n2);
        e = new string(strs.str());

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

    while (!dump.empty())
    {
        dump.pop();
        string *n = InterpretTerm(dump.top());
        double n1 = stod(*e);
        double n2 = stod(*n);

        ostringstream strs;
        strs << (n1 + n2);
        e = new string(strs.str());

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

    while (!dump.empty())
    {
        ASTNode *relationalOp = dump.top();
        string *v = relationalOp->getToken()->value;
        dump.pop();
        string *n;
        ASTNode *o = dump.top();
        if(o->getToken()->type == EQUALS)
        {
            v = &(v->append("="));
            dump.pop();
            n = InterpretSimpleExpression(dump.top());
        }
        else 
        {
            n = InterpretSimpleExpression(dump.top());
        }

        if (strcmp(v->c_str(), "<") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if (n2 < n1)
                e = new string("true");
            else
                e = new string("false");
        }
        if (strcmp(v->c_str(), ">") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if (n2 > n1)
                e = new string("true");
            else
                e = new string("false");
        }
        if (strcmp(v->c_str(), "<=") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if (n2 <= n1)
                e = new string("true");
            else
                e = new string("false");
        }
        if (strcmp(v->c_str(), ">=") == 0)
        {
            double n1 = stod(*e);
            double n2 = stod(*n);

            if (n2 >= n1)
                e = new string("true");
            else
                e = new string("false");
        }

        const char *E = e->c_str();
        const char *N = n->c_str();

        if (strcmp(v->c_str(), "==") == 0)
        {
            if (strcmp(E, N) == 0)
                e = new string("true");
            else
                e = new string("false");
        }
        if (strcmp(v->c_str(), "!=") == 0)
        {
            if (strcmp(E, N) == 0)
                e = new string("false");
            else
                e = new string("true");
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

    rf->update(identifier->getToken(), e);
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

void Interpreter::InterpretIfStatement(ASTNode *ifStatement)
{
    stack<ASTNode *> dump = *(ifStatement->getNodes());
    ASTNode *firstBlock = dump.top();
    ASTNode *secondBlock = NULL;

    dump.pop();
    if (dump.top()->getToken()->type == ELSE)
    {
        dump.pop();
        secondBlock = dump.top();
        dump.pop();
    }

    dump.pop();

    ASTNode *expression = dump.top();
    const char *e = InterpretExpression(expression)->c_str();

    if (strcmp(e, "true") == 0)
    {
        rf->push();
        if(secondBlock != NULL)
            InterpretBlock(secondBlock);
        else InterpretBlock(firstBlock);
        rf->pop();
    }
    else
    {
        if(secondBlock != NULL)
        {
            rf->push();
            InterpretBlock(firstBlock);
            rf->pop();
        }
    }
}

void Interpreter::InterpretWhileStatement(ASTNode *whileStatement)
{
    stack<ASTNode *> dump = *(whileStatement->getNodes());
    ASTNode *block = dump.top();
    dump.pop();
    dump.pop();
    string *e = InterpretExpression(dump.top());

    while (strcmp(e->c_str(), "false") != 0)
    {
        rf->push();
        InterpretBlock(block);
        rf->pop();
        e = InterpretExpression(dump.top());
    }
}

void Interpreter::InterpretFunctionDecl(ASTNode *functionDecl)
{
    stack<ASTNode *> dump = *(functionDecl->getNodes());
    dump.pop();
    dump.pop();
    dump.pop();
    dump.pop();
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();
    this->functionDefs->insert(pair<string, ASTNode *>(*(identifier->getToken()->value), functionDecl));
}

string *Interpreter::InterpretFunctionCall(ASTNode *functionCall)
{
    stack<ASTNode *> dump = *(functionCall->getNodes());
    dump.pop();
    ASTNode *actualParams = dump.top();
    stack<ASTNode *> ap = *(actualParams->getNodes());

    dump.pop();
    dump.pop();

    ASTNode *identifier = dump.top();
    ASTNode *functionDef = this->functionDefs->at(*(identifier->getToken()->value));

    stack<ASTNode *> dump2 = *(functionDef->getNodes());
    ASTNode *block = dump2.top();
    dump2.pop();
    dump2.pop();
    dump2.pop();
    dump2.pop();
    ASTNode *formalParams = dump2.top();

    stack<ASTNode *> fp = *(formalParams->getNodes());

    if (!fp.empty())
    {
        rf->push();

        ASTNode *formalParam = fp.top();
        ASTNode *actualParam = ap.top();

        stack<ASTNode *> dump = *(formalParam->getNodes());
        dump.pop();
        dump.pop();
        ASTNode *identifier = dump.top();
        string *e = InterpretExpression(actualParam);
        rf->insert(identifier->getToken(), e);

        fp.pop();
        ap.pop();

        while (!fp.empty())
        {
            fp.pop();
            ap.pop();

            ASTNode *formalParam = fp.top();
            ASTNode *actualParam = ap.top();

            stack<ASTNode *> dump = *(formalParam->getNodes());
            dump.pop();
            dump.pop();
            ASTNode *identifier = dump.top();
            string *e = InterpretExpression(actualParam);
            rf->insert(identifier->getToken(), e);

            fp.pop();
            ap.pop();
        }
    }

    string *e = InterpretFunctionBlock(block);
    rf->pop();

    return e;
}

string *Interpreter::InterpretStatement(ASTNode *statement)
{
    stack<ASTNode *> dump = *(statement->getNodes());
    ASTNode *node = dump.top();

    if(node->getToken()->type == SEMI_COLON)
    {
        dump.pop();
        node = dump.top();
    }

    switch(node->getToken()->type)
    {
        case VARIABLE_DECL:
        {
            InterpretVariableDecl(node);
            return NULL;
        }
        case ASSIGNMENT:
        {
            InterpretAssignment(node);
            return NULL;
        }
        case PRINT_STATEMENT:
        {
            InterpretPrintStatement(node);
            return NULL;
        }
        case IF_STATEMENT:
        {
            InterpretIfStatement(node);
            return NULL;
        }
        case WHILE_STATEMENT:
        {
            InterpretWhileStatement(node);
            return NULL;
        }
        case RETURN_STATEMENT:
        {
            return InterpretReturnStatement(node);
        }
        case FUNCTION_DECL:
        {
            InterpretFunctionDecl(node);
            return NULL;
        }
        case BLOCK:
        {
            InterpretBlock(node);
            return NULL;
        }
    }
}

void Interpreter::InterpretBlock(ASTNode *block)
{
    stack<ASTNode *> dump = *(block->getNodes());
    stack<ASTNode *> *reverse = new stack<ASTNode *>();

    while(!dump.empty())
    {
        reverse->push(dump.top());
        dump.pop();
    }

    reverse->pop();

    while(reverse->top()->getToken()->type != RIGHT_CURLY)
    {
        ASTNode *statement = reverse->top();
        InterpretStatement(statement);
        reverse->pop();
    }
}

string *Interpreter::InterpretFunctionBlock(ASTNode *block)
{
    stack<ASTNode *> dump = *(block->getNodes());
    stack<ASTNode *> *reverse = new stack<ASTNode *>();

    while(!dump.empty())
    {
        reverse->push(dump.top());
        dump.pop();
    }

    reverse->pop();

    while(reverse->top()->getToken()->type != RIGHT_CURLY)
    {
        string *e = InterpretStatement(reverse->top());
        if(e != NULL) return e;
        reverse->pop();
    }
}

void Interpreter::InterpretProgram(ASTNode *program)
{
    stack<ASTNode *> dump = *(program->getNodes());
    stack<ASTNode *> *reverse = new stack<ASTNode *>();

    while(!dump.empty())
    {
        reverse->push(dump.top());
        dump.pop();
    }
    
    while(!reverse->empty())
    {
        InterpretStatement(reverse->top());
        reverse->pop();
    }
}