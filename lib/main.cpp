#include <iostream>
#include <string>
#include <stack>
#include "Token.h"
#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"
#include "./Parser/ASTNodes.h"
#include "./SemanticAnalyzer/SemanticAnalyzer.h"
#include "./Execution/Interpreter.h"

using namespace std;

const char *loc = "./scripts/s1.minilang";

void printStack(stack<ASTNode *> *s)
{
    for (stack<ASTNode *> dump = *s; !dump.empty(); dump.pop())
        cout << *(dump.top()->getToken()->value) << endl;
}

int main()
{
    Parser *parser = new Parser(loc);

    ASTNode *program = parser->ParseProgram();

    SemanticAnalyzer *analyzer = new SemanticAnalyzer(program);

    cout << analyzer->AnalyzeProgram(program) << endl;

    cout << *(program->getToken()->value) << endl;

    // Interpreter *interpreter = new Interpreter();
    // interpreter->InterpretProgram(program);

    return 0;
}