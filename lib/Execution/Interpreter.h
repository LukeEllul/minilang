#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stack>
#include <string>
#include <map>
#include "../Token.h"
#include "../SemanticAnalyzer/SymbolTable.h"
#include "../Parser/ASTNodes.h"
#include "Reference.h"

using namespace std;

class Interpreter
{
  private:
    Reference *rf;
    map<string, ASTNode *> *functionDefs;

  public:
    Interpreter();

    string *InterpretFactor(ASTNode *factor);
    string *InterpretTerm(ASTNode *term);
    string *InterpretSimpleExpression(ASTNode *simpleExpression);
    string *InterpretExpression(ASTNode *expression);

    string *InterpretFunctionCall(ASTNode *functionCall);
    string *InterpretFunctionBlock(ASTNode *block);

    string *InterpretAssignment(ASTNode *assignment);
    string* InterpretVariableDecl(ASTNode *veriableDecl);
    void InterpretPrintStatement(ASTNode *printStatement);

    string *InterpretReturnStatement(ASTNode *returnStatement);

    void InterpretIfStatement(ASTNode *ifStatement);
    void InterpretWhileStatement(ASTNode *whileStatement);

    void InterpretFormalParam(ASTNode *formalParam);
    void InterpretFormalParams(ASTNode *formalParams);

    void InterpretFunctionDecl(ASTNode *functionDecl);

    string *InterpretStatement(ASTNode *statment);

    void InterpretBlock(ASTNode *block);
    void InterpretProgram(ASTNode *program);

    Reference *getRef();
};

#endif