#include <iostream>
#include <string>
#include <stack>
#include "Token.h"
#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"
#include "./Parser/ASTNodes.h"

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

    cout << program->fail << endl;

    cout << *(program->getToken()->value) << endl;

    stack<ASTNode*> *s = program->getNodes();

    cout << s->top()->getNodes()->top()->getNodes()->size() << endl;

    printStack(s->top()->getNodes()->top()->getNodes());

    cout << s->top()->getNodes()->top()->getToken()->type << endl;

    return 0;
}