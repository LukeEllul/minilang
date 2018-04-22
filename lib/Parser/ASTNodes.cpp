#include <string>
#include <stack>
#include "../Token.h"
#include "ASTNodes.h"

using namespace std;

ASTNode::ASTNode(TokenType type)
{
    Token *token = new Token();
    token->type = type;
    token->value = new string();
    this->token = token;
    this->ASTNodes = new stack<ASTNode*>();
}

stack<ASTNode*> *ASTNode::getNodes()
{
    return this->ASTNodes;
}

Token *ASTNode::getToken()
{
    return this->token;
}

void ASTNode::pushNode(ASTNode *node)
{
    this->ASTNodes->push(node);
}

ASTNode *ASTNode::popNode()
{
    ASTNode *node = this->ASTNodes->top();
    this->ASTNodes->pop();
    return node;
}

Token *ASTNode::pushValue(string *value)
{
    token->value->append(*value);
    return token;
}