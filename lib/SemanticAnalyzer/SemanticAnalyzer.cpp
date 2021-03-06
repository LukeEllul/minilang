#include <iostream>
#include <stack>
#include <string>
#include "../Token.h"
#include "../Parser/ASTNodes.h"
#include "SymbolTable.h"
#include "SemanticAnalyzer.h"

using namespace std;

SemanticAnalyzer::SemanticAnalyzer()
{
    this->st = new SymbolTable();
}

TokenType SemanticAnalyzer::GetType(string *s)
{
    if(s->compare("real") == 0)
        return REAL_LITERAL;
    if(s->compare("int") == 0)
        return INTEGER_LITERAL;
    if(s->compare("bool") == 0)
        return BOOLEAN_LITERAL;
    if(s->compare("string") == 0)
        return STRING_LITERAL;
}

TokenType SemanticAnalyzer::AnalyzeFactor(ASTNode *factor)
{
    Token *t = factor->getNodes()->top()->getToken();
    switch(t->type)
    {
        case LITERAL: return factor->getNodes()->top()->getNodes()->top()->getToken()->type;
        case IDENTIFIER:
            {
                TokenType type = st->lookup(t);
                return type;
            }
        case FUNCTION_CALL:
        {
            Token *identifier;
            stack<ASTNode*> dump = *(factor->getNodes()->top()->getNodes());
            dump.pop();
            dump.pop();
            dump.pop();
            identifier = dump.top()->getToken();
            return st->lookup(identifier);
        }
        case SUB_EXPRESSION:
        {
            ASTNode *subExpression = factor->getNodes()->top();
            stack<ASTNode*> dump = *(subExpression->getNodes());
            dump.pop();
            ASTNode *expression = dump.top();
            return AnalyzeExpression(expression);
        }
        case UNARY:
        {
            ASTNode *unary = factor->getNodes()->top();
            ASTNode *expression = unary->getNodes()->top();
            return AnalyzeExpression(expression);
        }
    }
}

TokenType SemanticAnalyzer::AnalyzeTerm(ASTNode *term)
{
    ASTNode *firstFactor = term->getNodes()->top();
    TokenType type = AnalyzeFactor(firstFactor);
    if(term->getNodes()->size() > 1)
    {
        if(type != INTEGER_LITERAL && type != REAL_LITERAL)
        {
            return INVALID;
        }
        stack<ASTNode*> dump = *(term->getNodes());
        dump.pop();

        while(!dump.empty())
        {
            dump.pop();
            TokenType thisType = AnalyzeFactor(dump.top());
            if(thisType == REAL_LITERAL)
            {
                type = thisType;
            }
            else if(thisType != INTEGER_LITERAL && thisType != REAL_LITERAL)
            {
                return INVALID;
            }
            dump.pop();
        }
    }

    return type;
}

TokenType SemanticAnalyzer::AnalyzeSimpleExpression(ASTNode *simpleExpression)
{
    ASTNode *firstTerm = simpleExpression->getNodes()->top();
    TokenType type = AnalyzeTerm(firstTerm);
    if(simpleExpression->getNodes()->size() > 1)
    {
        if(type != INTEGER_LITERAL && type != REAL_LITERAL)
        {
            return INVALID;
        }
        stack<ASTNode*> dump = *(simpleExpression->getNodes());
        dump.pop();

        while(!dump.empty())
        {
            dump.pop();
            TokenType thisType = AnalyzeTerm(dump.top());
            if(thisType == REAL_LITERAL)
            {
                type = thisType;
            }
            else if(thisType != INTEGER_LITERAL && thisType != REAL_LITERAL)
            {
                return INVALID;
            }
            dump.pop();
        }
    }

    return type;
}

TokenType SemanticAnalyzer::AnalyzeExpression(ASTNode *expression)
{
    ASTNode *firstSimpleExpression = expression->getNodes()->top();
    TokenType type = AnalyzeSimpleExpression(firstSimpleExpression);
    if(expression->getNodes()->size() > 1)
    {
        if(type != INTEGER_LITERAL && type != REAL_LITERAL)
        {
            return INVALID;
        }
        stack<ASTNode*> dump = *(expression->getNodes());
        dump.pop();

        while(!dump.empty())
        {
            dump.pop();
            TokenType thisType = AnalyzeSimpleExpression(dump.top());
            if(thisType == REAL_LITERAL)
            {
                type = thisType;
            }
            else if(thisType != INTEGER_LITERAL && thisType != REAL_LITERAL)
            {
                return INVALID;
            }
            dump.pop();
        }
    }

    return type;
}

bool SemanticAnalyzer::checkAssignment(ASTNode *assignment)
{
    stack<ASTNode*> dump = *(assignment->getNodes());
    ASTNode *expression = dump.top();
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();

    TokenType identifierType = st->lookup(identifier->getToken());
    TokenType expressionType = AnalyzeExpression(expression);

    return identifierType == expressionType;
}

bool SemanticAnalyzer::checkVariableDecl(ASTNode *variableDecl)
{
    stack<ASTNode*> dump = *(variableDecl->getNodes());
    ASTNode *expression = dump.top();
    dump.pop();
    dump.pop();
    ASTNode *type = dump.top();
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();

    TokenType expressionType = AnalyzeExpression(expression);
    TokenType typeType = GetType(type->getToken()->value);

    if(expressionType != typeType)
        return false;

    try
    {
        st->currentScope()->at(*(identifier->getToken()->value));
        return false;
    } 
    catch(out_of_range &e)
    {
        st->insert(identifier->getToken(), expressionType);
        return true;
    }
}

bool SemanticAnalyzer::checkFunctionDecl(ASTNode *functionDecl)
{
    stack<ASTNode*> dump = *(functionDecl->getNodes());
    ASTNode *block = dump.top();
    dump.pop();
    TokenType type = GetType(dump.top()->getToken()->value);
    dump.pop();
    dump.pop();
    dump.pop();
    ASTNode *formalParams = dump.top();
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();
    try
    {
        st->currentScope()->at(*(identifier->getToken()->value));
        return false;
    } 
    catch(out_of_range &e)
    {
        st->insert(identifier->getToken(), type);
    }
    st->push();
    checkFormalParams(formalParams);

    if(checkBlock(block))
    {
        st->pop();
        return true;
    }
    else 
    {
        st->pop();
        return false;
    }
}

bool SemanticAnalyzer::checkStatemant(ASTNode *statement)
{
    stack<ASTNode*> dump = *(statement->getNodes());
    TokenType type = dump.top()->getToken()->type;

    if(type == IF_STATEMENT)
        return checkIfStatement(dump.top());
    if(type == WHILE_STATEMENT)
        return checkWhileStatement(dump.top());
    if(type == FUNCTION_DECL)
        return checkFunctionDecl(dump.top());
    if(type == BLOCK)
    {
        st->push();
        if(checkBlock(dump.top()))
        {
            st->pop();
            return true;
        }
        else
        {
            st->pop();
            return false;
        }
    }
    else 
    {
        dump.pop();
        type = dump.top()->getToken()->type;

        if(type == VARIABLE_DECL)
            return checkVariableDecl(dump.top());
        if(type == ASSIGNMENT)
            return checkAssignment(dump.top());
        else return true;
    }
}

bool SemanticAnalyzer::checkIfStatement(ASTNode* ifStatement)
{
    stack<ASTNode*> dump = *(ifStatement->getNodes());
    ASTNode *firstBlock = dump.top();
    ASTNode *secondBlock = NULL;
    dump.pop();
    if(dump.top()->getToken()->type == ELSE)
    {
        dump.pop();
        secondBlock = dump.top();
        dump.pop();
    }
    dump.pop();
    ASTNode *expression = dump.top();
    if(AnalyzeExpression(expression) == INVALID)
        return false;
    
    st->push();
    if(!checkBlock(firstBlock))
        return (st->pop(), false);
    st->pop();
    if(secondBlock == NULL)
        return true;
    st->push();
    if(!checkBlock(secondBlock))
        return (st->pop(), false);
    st->pop();

    return true;
}

bool SemanticAnalyzer::checkWhileStatement(ASTNode* whileStatement)
{
    stack<ASTNode*> dump = *(whileStatement->getNodes());
    ASTNode *block = dump.top();
    dump.pop();
    dump.pop();
    ASTNode *expression = dump.top();
    if(AnalyzeExpression(expression) == INVALID)
        return false;
    
    st->push();
    if(!checkBlock(block))
        return (st->pop(), false);

    st->pop();
    return true;
}

bool SemanticAnalyzer::checkFormalParam(ASTNode *formalParam)
{
    stack<ASTNode*> dump = *(formalParam->getNodes());
    TokenType type = GetType(dump.top()->getToken()->value);
    dump.pop();
    dump.pop();
    ASTNode *identifier = dump.top();
    st->insert(identifier->getToken(), type);

    return true;
}

bool SemanticAnalyzer::checkFormalParams(ASTNode *formalParams)
{
    stack<ASTNode*> dump = *(formalParams->getNodes());
    ASTNode *formalParam = dump.top();
    checkFormalParam(formalParam);
    dump.pop();

    while(!dump.empty())
    {
        dump.pop();
        formalParam = dump.top();
        checkFormalParam(formalParam);
        dump.pop();
    }

    return true;
}

bool SemanticAnalyzer::checkBlock(ASTNode *block)
{
    stack<ASTNode*> reverse = *(block->getNodes());
    stack<ASTNode*> *dump = new stack<ASTNode*>();

    while(!reverse.empty())
    {
        dump->push(reverse.top());
        reverse.pop();
    }

    dump->pop();
    ASTNode *node = dump->top();

    while(node->getToken()->type != RIGHT_CURLY)
    {
        if(!checkStatemant(node))
            return false;
        dump->pop();
        node = dump->top();
    }

    return true;
}

bool SemanticAnalyzer::AnalyzeProgram(ASTNode *program)
{
    stack<ASTNode*> reverse = *(program->getNodes());
    stack<ASTNode *> *dump = new stack<ASTNode*>();

    while(!reverse.empty())
    {
        dump->push(reverse.top());
        reverse.pop();
    }

    ASTNode *statement = dump->top();
    if(!checkStatemant(statement))
        return false;

    dump->pop();

    while(!dump->empty())
    {
        statement = dump->top();
        if(!checkStatemant(statement))
            return false;
        dump->pop();
    }

    return true;
}