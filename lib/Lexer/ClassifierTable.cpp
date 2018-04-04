#include <iostream>
#include <string>
#include <map>
#include "../Token.cpp"

using namespace std;

map<char, TokenType> *ClassifierTable = new map<char, TokenType>(
    {
        {'1', DIGIT},
        {'2', DIGIT},
        {'3', DIGIT},
        {'4', DIGIT},
        {'5', DIGIT},
        {'6', DIGIT},
        {'7', DIGIT},
        {'8', DIGIT},
        {'9', DIGIT},
        {'0', DIGIT},

        {'a', LETTER},
        {'b', LETTER},
        {'c', LETTER},
        {'d', LETTER},
        {'e', LETTER},
        {'f', LETTER},
        {'g', LETTER},
        {'h', LETTER},
        {'i', LETTER},
        {'j', LETTER},
        {'k', LETTER},
        {'l', LETTER},
        {'m', LETTER},
        {'n', LETTER},
        {'o', LETTER},
        {'p', LETTER},
        {'q', LETTER},
        {'r', LETTER},
        {'s', LETTER},
        {'t', LETTER},
        {'u', LETTER},
        {'v', LETTER},
        {'w', LETTER},
        {'x', LETTER},
        {'y', LETTER},
        {'z', LETTER},

        {'A', LETTER},
        {'B', LETTER},
        {'C', LETTER},
        {'D', LETTER},
        {'E', LETTER},
        {'F', LETTER},
        {'G', LETTER},
        {'H', LETTER},
        {'I', LETTER},
        {'J', LETTER},
        {'K', LETTER},
        {'L', LETTER},
        {'M', LETTER},
        {'N', LETTER},
        {'O', LETTER},
        {'P', LETTER},
        {'Q', LETTER},
        {'R', LETTER},
        {'S', LETTER},
        {'T', LETTER},
        {'U', LETTER},
        {'V', LETTER},
        {'W', LETTER},
        {'X', LETTER},
        {'Y', LETTER},
        {'Z', LETTER},

        {'_', IDENTIFIER},

        {'*', MULTIPLICATIVE_OP},
        {'/', MULTIPLICATIVE_OP},

        {'+', ADDITIVE_OP},
        {'-', ADDITIVE_OP},

        {'<', RELATIONAL_OP},
        {'>', RELATIONAL_OP},

        {'(', LEFT_BRACKET},
        {')', RIGHT_BRACKET},

        {',', COMMA},
        {'=', EQUALS},
        {':', COLON}
    }
);

int main()
{
    for (auto it = ClassifierTable->begin(); it != ClassifierTable->end(); ++it)
      cout << it->first << " = " << it->second << endl;

   return 0;

}