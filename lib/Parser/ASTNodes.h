#ifndef ASTNODES_H
#define ASTNODES_H
#include "../Token.h"

class ASTNode 
{
    private:
        const ASTNode *ASTNodes;
        const Token *token;

    public:
        ASTNode(const ASTNode *ASTnodes, Token *token);
        const ASTNode *getNodes();
        const Token *getToken();
};

#endif