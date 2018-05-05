#include <string>
#include <stack>
#include "../Token.h"
#include "ASTNodes.h"

using namespace std;

ASTNode::ASTNode(Token *token)
{
    this->token = token;
    this->ASTNodes = new stack<ASTNode*>();
    this->fail = false;
}

stack<ASTNode*> *ASTNode::getNodes()
{
    return this->ASTNodes;
}

void ASTNode::setNodes(stack<ASTNode*> *ASTNodes)
{
    this->ASTNodes = ASTNodes;
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

bool ASTNode::leaf()
{
    if(this->ASTNodes->empty())
        return true;
    else return false;
} 