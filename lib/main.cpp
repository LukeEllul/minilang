#include <iostream>
#include <string>
#include "Token.h"
#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"

using namespace std;

const char *loc = "./scripts/s1.minilang";

int main()
{
    Parser *parser = new Parser(loc);

    ASTNode *program = parser->ParseProgram();

    cout << program->fail << endl;
    cout << (*program->getToken()->value) << endl;

    return 0;
}