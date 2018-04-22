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
        ASTNode(TokenType type);
        stack<ASTNode*> *getNodes();
        Token *getToken();
        void pushNode(ASTNode *node);
        ASTNode *popNode();

        Token *pushValue(string *value);
};

#endif