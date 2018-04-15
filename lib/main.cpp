#include <iostream>
#include "Token.h"
#include "./Lexer/Lexer.h"

using namespace std;

int main()
{
    Lexer *lexer = new Lexer("./scripts/s1.minilang");

    Token *token = lexer->NextToken();

    while (token->type != TOK_EOF && token->type != INVALID)
    {
        if (token->type != WHITE_SPACE && token->type != NEW_LINE)
        {
            cout << "Type" << endl;
            cout << token->type << endl;

            cout << "lexeme" << endl;
            cout << *token->value << endl;

            cout << endl;
        }

        token = lexer->NextToken();
    }

    return 0;
}