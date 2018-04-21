#include "../Token.h"
#include "ASTNodes.h"

using namespace std;

ASTNode::ASTNode(const ASTNode *ASTNodes, Token *token)
{
    this->ASTNodes = ASTNodes;
    this->token = token;
}

const ASTNode *ASTNode::getNodes()
{
    return this->ASTNodes;
}

const Token *ASTNode::getToken()
{
    return this->token;
}