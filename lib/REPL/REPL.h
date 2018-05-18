#ifndef REPL_H
#define REPL_H
#include <stack>
#include <string>
#include "../Token.h"
#include "../Parser/Parser.h"
#include "../Parser/ASTNodes.h"
#include "../SemanticAnalyzer/SemanticAnalyzer.h"
#include "../Execution/Interpreter.h"

using namespace std;

class REPL
{
    private:
        string *inputString;
        Token* ans;
        
        Parser *parser;
        SemanticAnalyzer *analyzer;
        Interpreter *interpreter;

    public:
        REPL();

        string *getStatement(string *input);

        void ReadVariableDecl(ASTNode *variableDecl);
        void ReadAssignment(ASTNode *assignment);
        void ReadExpression(ASTNode *expression);
        void ReadStatement(ASTNode *statement);

        void ParseInput(string *input);
        void LoadProgram(const char* loc);

        void ReadLine(string *input);

        void updateAns();

        Token *getAnswer();
};

#endif