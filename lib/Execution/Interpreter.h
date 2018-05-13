#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stack>
#include <string>
#include "../Token.h"
#include "../SemanticAnalyzer/SymbolTable.h"
#include "../Parser/ASTNodes.h"
#include "Reference.h"

using namespace std;

class Interpreter 
{
    private:
        Reference *rf;

    public:
        Interpreter(ASTNode *program);

        string *InterpretFactor(ASTNode *factor);
        string *InterpretTerm(ASTNode *term);
        string *InterpretSimpleExpression(ASTNode *simpleExpression);
        string *InterpretExpression(ASTNode *expression);

        void InterpretAssignment(ASTNode *assignment);
        void InterpretVariableDecl(ASTNode *veriableDecl);
        void InterpretPrintStatement(ASTNode *printStatement);

        string *InterpretReturnStatement(ASTNode *returnStatement);

        void InterpretIfStatement(ASTNode *ifStatement);
        void InterpretWhileStatement(ASTNode *whileStatement);

        void InterpretFormalParam(ASTNode *formalParam);
        void InterpretFormalParams(ASTNode *formalParams);

        void InterpretFunctionDecl(ASTNode *functionDecl);

        void InterpretStatement(ASTNode *statment);

        void InterpretBlock(ASTNode *block);
        void InterpretProgram(ASTNode *program);
};

#endif