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

        TokenType GetType(string *s);

        TokenType AnalyzeFactor(ASTNode *factor);
        TokenType AnalyzeTerm(ASTNode *term);
        TokenType AnalyzeSimpleExpression(ASTNode *simpleExpression);
        TokenType AnalyzeExpression(ASTNode *expression);
        
        bool checkBlock(ASTNode *block);
        bool checkAssignment(ASTNode *assignment);
        bool checkVariableDecl(ASTNode *variableDecl);
        bool checkIfStatement(ASTNode *ifStatement);
        bool checkWhileStatement(ASTNode *whileStatement);
        bool checkFormalParam(ASTNode *formalParam);
        bool checkFormalParams(ASTNode *formalParams);
        bool checkFunctionDecl(ASTNode *functionDecl);

        bool checkStatemant(ASTNode *statement);

        bool AnalyzeProgram();
};

#endif