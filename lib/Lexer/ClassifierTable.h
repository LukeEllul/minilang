#ifndef CLASSIFIER_TABLE
#define CLASSIFIER_TABLE
#include <iostream>
#include <string>
#include <map>
#include "../Token.h"

using namespace std;

map<char, TokenType> *ClassifierTableX = new map<char, TokenType>(
    {
        {'1', (TokenType)DIGIT},
        {'2', (TokenType)DIGIT},
        {'3', (TokenType)DIGIT},
        {'4', (TokenType)DIGIT},
        {'5', (TokenType)DIGIT},
        {'6', (TokenType)DIGIT},
        {'7', (TokenType)DIGIT},
        {'8', (TokenType)DIGIT},
        {'9', (TokenType)DIGIT},
        {'0', (TokenType)DIGIT},

        {'a', (TokenType)LETTER},
        {'b', (TokenType)LETTER},
        {'c', (TokenType)LETTER},
        {'d', (TokenType)LETTER},
        {'e', (TokenType)LETTER},
        {'f', (TokenType)LETTER},
        {'g', (TokenType)LETTER},
        {'h', (TokenType)LETTER},
        {'i', (TokenType)LETTER},
        {'j', (TokenType)LETTER},
        {'k', (TokenType)LETTER},
        {'l', (TokenType)LETTER},
        {'n', (TokenType)LETTER},
        {'m', (TokenType)LETTER},
        {'o', (TokenType)LETTER},
        {'p', (TokenType)LETTER},
        {'q', (TokenType)LETTER},
        {'r', (TokenType)LETTER},
        {'s', (TokenType)LETTER},
        {'t', (TokenType)LETTER},
        {'u', (TokenType)LETTER},
        {'v', (TokenType)LETTER},
        {'w', (TokenType)LETTER},
        {'x', (TokenType)LETTER},
        {'y', (TokenType)LETTER},
        {'z', (TokenType)LETTER},

        {'A', (TokenType)LETTER},
        {'B', (TokenType)LETTER},
        {'C', (TokenType)LETTER},
        {'D', (TokenType)LETTER},
        {'E', (TokenType)LETTER},
        {'F', (TokenType)LETTER},
        {'G', (TokenType)LETTER},
        {'H', (TokenType)LETTER},
        {'I', (TokenType)LETTER},
        {'J', (TokenType)LETTER},
        {'K', (TokenType)LETTER},
        {'L', (TokenType)LETTER},
        {'M', (TokenType)LETTER},
        {'N', (TokenType)LETTER},
        {'O', (TokenType)LETTER},
        {'P', (TokenType)LETTER},
        {'Q', (TokenType)LETTER},
        {'R', (TokenType)LETTER},
        {'S', (TokenType)LETTER},
        {'T', (TokenType)LETTER},
        {'U', (TokenType)LETTER},
        {'V', (TokenType)LETTER},
        {'W', (TokenType)LETTER},
        {'X', (TokenType)LETTER},
        {'Y', (TokenType)LETTER},
        {'Z', (TokenType)LETTER},

        {'*', (TokenType)MULTIPLICATIVE_OP},
        {'/', (TokenType)MULTIPLICATIVE_OP},

        {'+', (TokenType)ADDITIVE_OP},
        {'-', (TokenType)ADDITIVE_OP},

        {'<', (TokenType)RELATIONAL_OP},
        {'>', (TokenType)RELATIONAL_OP},

        {'(', (TokenType)LEFT_BRACKET},
        {')', (TokenType)RIGHT_BRACKET},

        {',', (TokenType)COMMA},
        {'.', (TokenType)PERIOD},
        {'=', (TokenType)EQUALS},
        {':', (TokenType)COLON},
        {'_', (TokenType)UNDERSCORE},
        {'!', (TokenType)EXCLAMATION_MARK},
        {'"', (TokenType)INVERTED_COMMA},

        {EOF, (TokenType)TOK_EOF}
    }
);

#endif

// int main()
// {
//     for (auto it = ClassifierTable->begin(); it != ClassifierTable->end(); ++it)
//       cout << it->first << " = " << it->second << endl;

//    return 0;

// }