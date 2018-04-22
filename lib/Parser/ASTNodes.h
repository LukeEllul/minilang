#ifndef ASTNODES_H
#define ASTNODES_H
#include <stack>
#include "../Token.h"

using namespace std;

class ASTNode 
{
    private:
        stack<ASTNode*> *ASTNodes;
        Token *token;

    public:
        ASTNode(Token *token);
        stack<ASTNode*> *getNodes();
        void setNodes(stack<ASTNode*> *ASTNodes);
        Token *getToken();
        void pushNode(ASTNode *node);
        ASTNode *popNode();

        Token *pushValue(string *value);

        bool fail;
};

#endif