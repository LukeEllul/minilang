#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H
#include <stack>
#include <string>
#include "../Token.h"
#include "../Parser/ASTNodes.h"
#include "SymbolTable.h"

using namespace std;

class SemanticAnalyzer 
{
    private:
        ASTNode *tree;
        SymbolTable *st;

    public:
        SemanticAnalyzer(ASTNode *program);

        TokenType AnalyzeFactor(ASTNode *factor);

        TokenType AnalyzeTerm(ASTNode *term);
        TokenType AnalyzeSimpleExpression(ASTNode *simpleExpression);
        TokenType AnalyzeExpression(ASTNode *expression);
        
        bool checkAssignment(ASTNode *assignment);
        bool checkVariableDecl(ASTNode *variableDecl);

        bool AnalyzeProgram();
};

#endif