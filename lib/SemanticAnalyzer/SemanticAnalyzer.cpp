#include <stack>
#include <string>
#include "../Token.h"
#include "../Parser/ASTNodes.h"
#include "SymbolTable.h"
#include "SemanticAnalyzer.h"

using namespace std;

SemanticAnalyzer::SemanticAnalyzer(ASTNode *program)
{
    this->tree = program;
    this->st = new SymbolTable();
}

TokenType SemanticAnalyzer::AnalyzeFactor(ASTNode *factor)
{
    Token *t = factor->getNodes()->top()->getToken();
    switch(t->type)
    {
        case LITERAL: return LITERAL;
        case IDENTIFIER:
            {
                TokenType type = st->lookup(t);
                return type;
            }
        case FUNCTION_CALL:
        {
            Token *identifier;
            stack<ASTNode*> dump = *(factor->getNodes());
            while(!dump.empty())
            {
                identifier = dump.top()->getToken();
                dump.pop();
            }
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
    TokenType typeType = type->getToken()->type;
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
    }
}