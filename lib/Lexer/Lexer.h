#include <string>
#include <map>
#include "../Token.cpp"

using namespace std;

class Lexer 
{
    private:
        string *inputString;
        char currentChar;
        int currentPosition;

        char NextChar();
        map<char,TokenType> *ClassifierTable;
        TokenType const *TokenTypeTable;
        TokenType const (*TransitionTable)[17];

    public:
        Token *NextToken();
        Lexer(string *filePath);
        ~Lexer();
};