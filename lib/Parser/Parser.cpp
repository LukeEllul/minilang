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
            n = ParseIdentifier();
            this->counting = false;
            if(n->fail)
            {
                backTrack();
                n = ParseFunctionCall();
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