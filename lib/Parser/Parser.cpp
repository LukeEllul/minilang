#include <string>
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

ASTNode *Parser::ParseStringLiteral()
{
    ASTNode *node = new ASTNode(STRING_LITERAL);

    if (currentToken->type == INVERTED_COMMA)
    {
        node->pushValue(currentToken->value);
        while (nextToken()->type == PRINTABLE)
        {
            node->pushValue(currentToken->value);
        }
        if (currentToken->type == INVERTED_COMMA)
        {
            node->pushValue(currentToken->value);
            return node;
        }

        return Fail(node->getToken(), currentToken);
    }
}