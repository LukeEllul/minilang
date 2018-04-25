#include <string>
#include <stack>
#include <string.h>
#include "../Token.h"
#include "ASTNodes.h"
#include "../Lexer/Lexer.h"
#include "Parser.h"

using namespace std;

Parser::Parser(const char *fileName)
{
    this->lexer = new Lexer(fileName);
    this->currentToken = lexer->NextToken();
    this->count = 0;
    this->counting = false;
}

Token *Parser::nextToken()
{
    if(counting)
        count++;
    currentToken = lexer->NextToken();
    return currentToken;
}

void Parser::backTrack()
{
    for(int i = 0; i < count; i++)
    {
        this->lexer->goBack();
    }
    this->count = 0;
}

ASTNode *Parser::Fail(Token *token, Token *badToken, ASTNode *fail)
{
    ASTNode *node = new ASTNode(badToken);
    node->fail = true;
    node->pushNode(fail);
    return node;
}

ASTNode *Parser::ParseStringLiteral()
{
    Token *token = new Token();
    token->type = STRING_LITERAL;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if (currentToken->type == INVERTED_COMMA)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
        Token *t = nextToken();
        while (t->type == PRINTABLE || t->type == LETTER)
        {
            node->pushValue(currentToken->value);
            node->pushNode(new ASTNode(currentToken));
            t = nextToken();
        }
        if (currentToken->type == INVERTED_COMMA)
        {
            node->pushValue(currentToken->value);
            node->pushNode(new ASTNode(currentToken));
            nextToken();
            return node;
        }

        return Fail(node->getToken(), currentToken, node);
    }
}

ASTNode *Parser::ParseLiteral()
{
    Token *token = new Token();
    token->type = LITERAL;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    switch (currentToken->type)
    {
    case BOOLEAN_LITERAL:
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
    case INTEGER_LITERAL:
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
    case REAL_LITERAL:
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
    case INVERTED_COMMA:
        ASTNode *n = ParseStringLiteral();
        if (n->fail)
        {
            node->pushNode(n);
            return Fail(node->getToken(), currentToken, node);
        }
        node->pushValue(n->getToken()->value);
        node->pushNode(n);
    default:
        return Fail(node->getToken(), currentToken, node);
    }

    nextToken();
    return node;
}

ASTNode *Parser::ParseIdentifier()
{
    Token *token = new Token();
    token->type = IDENTIFIER;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if (currentToken->type == LETTER || currentToken->type == IDENTIFIER)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
        Token *t = nextToken();
        while (t->type == LETTER || t->type == IDENTIFIER || t->type == DIGIT)
        {
            node->pushValue(currentToken->value);
            node->pushNode(new ASTNode(currentToken));
            t = nextToken();
        }
        return node;
    }

    return Fail(node->getToken(), currentToken, node);
}

ASTNode *Parser::ParseRelationalOp()
{
    Token *token = new Token();
    token->type = RELATIONAL_OP;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if (currentToken->type == EQUALS)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
        nextToken();
        return node;
    }
    return node;
}

ASTNode *Parser::ParseActualParams()
{
    Token *token = new Token();
    token->type = ACTUAL_PARAMS;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if (expression->fail || currentToken->type != COMMA)
    {
        return Fail(node->getToken(), currentToken, node);
    }

    while (currentToken->type == COMMA)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));
        
        ASTNode *expression = ParseExpression();
        node->pushValue(expression->getToken()->value);
        node->pushNode(expression);

        if(expression->fail)
            return Fail(node->getToken(), currentToken, node);
    }

    return node;
}

ASTNode *Parser::ParseFunctionCall()
{
    Token *token = new Token();
    token->type = FUNCTION_CALL;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *identifier = ParseIdentifier();
    node->pushValue(identifier->getToken()->value);
    node->pushNode(identifier);

    if(identifier->fail || currentToken->type != LEFT_BRACKET)
        return Fail(node->getToken(), currentToken, node);
    
    nextToken();

    ASTNode *actualParams = ParseActualParams();
    node->pushValue(actualParams->getToken()->value);
    node->pushNode(actualParams);

    if(actualParams->fail || currentToken->type != RIGHT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();
    return node;
}

ASTNode *Parser::ParseSubExpression()
{
    Token *token = new Token();
    token->type = SUB_EXPRESSION;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    if(currentToken->type != LEFT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail || currentToken->type != RIGHT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();
    return node;
}

ASTNode *Parser::ParseUnary()
{
    Token *token = new Token();
    token->type = UNARY;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    if(currentToken->value->at(0) != '-' && currentToken->type != NOT)
        return Fail(node->getToken(), currentToken, node);

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseFactor()
{
    Token *token = new Token();
    token->type = FACTOR;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *n;

    switch(currentToken->type)
    {
        case BOOLEAN_LITERAL:
            n = ParseLiteral();
        case INTEGER_LITERAL:
            n = ParseLiteral();
        case REAL_LITERAL:
            n = ParseLiteral();
        case INVERTED_COMMA:
            n = ParseLiteral();
        case IDENTIFIER:
            this->counting = true;
            n = ParseFunctionCall();
            this->counting = false;
            if(n->fail)
            {
                backTrack();
                n = ParseIdentifier();
            }
        case ADDITIVE_OP:
            n = ParseUnary();
        case NOT:
            n = ParseUnary();
        case LEFT_BRACKET:
            n = ParseSubExpression();
        default:
            return Fail(node->getToken(), currentToken, node);
    }

    node->pushValue(n->getToken()->value);
    node->pushNode(n);

    if(n->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseTerm()
{
    Token *token = new Token();
    token->type = TERM;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *factor = ParseFactor();

    node->pushValue(factor->getToken()->value);
    node->pushNode(factor);

    if(factor->fail)
        return Fail(node->getToken(), currentToken, node);

    while(currentToken->type == MULTIPLICATIVE_OP)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();

        ASTNode *factor = ParseFactor();
        node->pushValue(factor->getToken()->value);
        node->pushNode(factor);

        if(factor->fail)
            return Fail(node->getToken(), currentToken, node);
    }

    return node;
}

ASTNode *Parser::ParseSimpleExpression()
{
    Token *token = new Token();
    token->type = SIMPLE_EXPRESSION;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *term = ParseTerm();

    node->pushValue(term->getToken()->value);
    node->pushNode(term);

    if(term->fail)
        return Fail(node->getToken(), currentToken, node);

    while(currentToken->type == ADDITIVE_OP)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();

        ASTNode *term = ParseTerm();
        node->pushValue(term->getToken()->value);
        node->pushNode(term);

        if(term->fail)
            return Fail(node->getToken(), currentToken, node);
    }

    return node;
}

ASTNode *Parser::ParseExpression()
{
    Token *token = new Token();
    token->type = EXPRESSION;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *simpleExpression = ParseSimpleExpression();

    node->pushValue(simpleExpression->getToken()->value);
    node->pushNode(simpleExpression);

    if(simpleExpression->fail)
        return Fail(node->getToken(), currentToken, node);

    while(currentToken->type == RELATIONAL_OP)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();

        ASTNode *simpleExpression = ParseSimpleExpression();
        node->pushValue(simpleExpression->getToken()->value);
        node->pushNode(simpleExpression);

        if(simpleExpression->fail)
            return Fail(node->getToken(), currentToken, node);
    }

    return node;
}

ASTNode *Parser::ParseAssignment()
{
    Token *token = new Token();
    token->type = ASSIGNMENT;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != SET)
    {
        return Fail(node->getToken(), currentToken, node);
    }

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *identifier = ParseIdentifier();

    node->pushValue(identifier->getToken()->value);
    node->pushNode(identifier);

    if(identifier->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != EQUALS)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseVariableDecl()
{
    Token *token = new Token();
    token->type = VARIABLE_DECL;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != VAR)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *identifier = ParseIdentifier();

    node->pushValue(identifier->getToken()->value);
    node->pushNode(identifier);

    if(identifier->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != COLON)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != TYPE)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != EQUALS)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();

    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParsePrintStatement()
{
    Token *token = new Token();
    token->type = PRINT_STATEMENT;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != PRINT)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseReturnStatement()
{
    Token *token = new Token();
    token->type = RETURN_STATEMENT;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != RETURN)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseIfStatement()
{
    Token *token = new Token();
    token->type = IF_STATEMENT;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != IF_STATEMENT)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != LEFT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != RIGHT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *block = ParseBlock();
    node->pushValue(block->getToken()->value);
    node->pushNode(block);

    if(block->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != ELSE)
        return node;

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    block = ParseBlock();
    node->pushValue(block->getToken()->value);
    node->pushNode(block);

    if(block->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseWhileStatement()
{
    Token *token = new Token();
    token->type = WHILE_STATEMENT;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    if(currentToken->type != WHILE)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != LEFT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *expression = ParseExpression();
    node->pushValue(expression->getToken()->value);
    node->pushNode(expression);

    if(expression->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != RIGHT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *block = ParseBlock();
    node->pushValue(block->getToken()->value);
    node->pushNode(block);

    if(block->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}

ASTNode *Parser::ParseFormalParam()
{
    Token *token = new Token();
    token->type = FORMAL_PARAM;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *identifier = ParseIdentifier();
    node->pushValue(identifier->getToken()->value);
    node->pushNode(identifier);

    if(identifier->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != COLON)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != TYPE)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    return node;
}

ASTNode *Parser::ParseFormalParams()
{
    Token *token = new Token();
    token->type = FORMAL_PARAMS;
    token->value = new string();
    ASTNode *node = new ASTNode(token);

    ASTNode *FormalParam = ParseFormalParam();
    node->pushValue(FormalParam->getToken()->value);
    node->pushNode(FormalParam);

    if(FormalParam->fail)
        return Fail(node->getToken(), currentToken, node);

    while(currentToken->type == COMMA)
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();

        ASTNode *FormalParam = ParseFormalParam();
        node->pushValue(FormalParam->getToken()->value);
        node->pushNode(FormalParam);

        if(FormalParam->fail)
            return Fail(node->getToken(), currentToken, node);
    }

    return node;
}

ASTNode *Parser::ParseFunctionDecl()
{
    Token *token = new Token();
    token->type = FUNCTION_DECL;
    token->value = new string();
    ASTNode *node = new ASTNode(currentToken);

    if(currentToken->type != DEF)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *identifier = ParseIdentifier();
    node->pushValue(identifier->getToken()->value);
    node->pushNode(identifier);

    if(identifier->fail)
        return Fail(node->getToken(), currentToken, node);

    if(currentToken->type != LEFT_BRACKET)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != RIGHT_BRACKET)
    {
        ASTNode *FormalParams = ParseFormalParams();
        node->pushValue(FormalParams->getToken()->value);
        node->pushNode(FormalParams);

        if(FormalParams->fail)
            return Fail(node->getToken(), currentToken, node);

        if(currentToken->type != RIGHT_BRACKET)
            return Fail(node->getToken(), currentToken, node);

        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();
    }
    else 
    {
        node->pushValue(currentToken->value);
        node->pushNode(new ASTNode(currentToken));

        nextToken();
    }

    if(currentToken->type != COLON)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    if(currentToken->type != TYPE)
        return Fail(node->getToken(), currentToken, node);

    node->pushValue(currentToken->value);
    node->pushNode(new ASTNode(currentToken));

    nextToken();

    ASTNode *block = ParseBlock();
    node->pushValue(block->getToken()->value);
    node->pushNode(block);

    if(block->fail)
        return Fail(node->getToken(), currentToken, node);

    return node;
}