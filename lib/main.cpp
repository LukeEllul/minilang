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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: minilang <path to minilang script>" << endl;
    }
    else
    {
        Parser *parser = new Parser(argv[1]);

        ASTNode *program = parser->ParseProgram();

        SemanticAnalyzer *analyzer = new SemanticAnalyzer();
        if (!analyzer->AnalyzeProgram(program))
        {
            cout << "You have semantic error/s" << endl;
        }
        else
        {
            Interpreter *interpreter = new Interpreter();
            interpreter->InterpretProgram(program);
        }
    }

    return 0;
}