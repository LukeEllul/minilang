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
        string *NextWord();
        map<char,char const*> *ClassifierTable;
        map<int,char const*> *TransitionTable;

    public:
        Token *NextToken();
        Lexer(string *filePath);
        ~Lexer();
};