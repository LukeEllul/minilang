#include <string>
#include <stack>
#include "../Token.h"
#include "ASTNodes.h"
#include "../Lexer/Lexer.h"
#include "Parser.h"

using namespace std;

Parser::Parser(const char *fileName)
{
    this->lexer = new Lexer(fileName);
    this->currentToken = lexer->NextToken();
}

Token *Parser::nextToken()
{
    currentToken = lexer->NextToken();
    return currentToken;
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