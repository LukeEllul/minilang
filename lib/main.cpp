#include <iostream>
#include "Token.h"
#include "./Lexer/Lexer.h"

using namespace std;

int main()
{
    Lexer *lexer = new Lexer("./scripts/s1.minilang");

    Token *token = lexer->NextToken();

    cout << token->type << endl;
    cout << *token->value << endl;

    token = lexer->NextToken();

    cout << token->type << endl;
    cout << *token->value << endl;

    return 0;
}