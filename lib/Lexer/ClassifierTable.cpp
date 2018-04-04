#include <iostream>
#include <string>
#include <map>
#include "../Token.cpp"

using namespace std;

map<char, TokenType> *ClassifierTable = new map<char, TokenType>(
    {
        {'1', TOK_Number},
        {'2', TOK_Number},
        {'3', TOK_Number},
        {'4', TOK_Number},
        {'5', TOK_Number},
        {'6', TOK_Number},
        {'7', TOK_Number},
        {'8', TOK_Number},
        {'9', TOK_Number},
        {'0', TOK_Number},

        {'-', TOK_ArithmeticOP},
        {'+', TOK_ArithmeticOP},
        {'*', TOK_ArithmeticOP},
        {'/', TOK_ArithmeticOP},

        {'<', TOK_BOOLEAN},
        {'>', TOK_BOOLEAN},

        {'a', TOK_ALPHA_SMALL},
        {'b', TOK_ALPHA_SMALL},
        {'c', TOK_ALPHA_SMALL},
        {'d', TOK_ALPHA_SMALL},
        {'e', TOK_ALPHA_SMALL},
        {'f', TOK_ALPHA_SMALL},
        {'g', TOK_ALPHA_SMALL},
        {'h', TOK_ALPHA_SMALL},
        {'i', TOK_ALPHA_SMALL},
        {'j', TOK_ALPHA_SMALL},
        {'k', TOK_ALPHA_SMALL},
        {'l', TOK_ALPHA_SMALL},
        {'m', TOK_ALPHA_SMALL},
        {'n', TOK_ALPHA_SMALL},
        {'o', TOK_ALPHA_SMALL},
        {'p', TOK_ALPHA_SMALL},
        {'q', TOK_ALPHA_SMALL},
        {'r', TOK_ALPHA_SMALL},
        {'s', TOK_ALPHA_SMALL},
        {'t', TOK_ALPHA_SMALL},
        {'u', TOK_ALPHA_SMALL},
        {'v', TOK_ALPHA_SMALL},
        {'w', TOK_ALPHA_SMALL},
        {'x', TOK_ALPHA_SMALL},
        {'y', TOK_ALPHA_SMALL},
        {'z', TOK_ALPHA_SMALL},

        {'A', TOK_ALPHA_LARGE},
        {'B', TOK_ALPHA_LARGE},
        {'C', TOK_ALPHA_LARGE},
        {'D', TOK_ALPHA_LARGE},
        {'E', TOK_ALPHA_LARGE},
        {'F', TOK_ALPHA_LARGE},
        {'G', TOK_ALPHA_LARGE},
        {'H', TOK_ALPHA_LARGE},
        {'I', TOK_ALPHA_LARGE},
        {'J', TOK_ALPHA_LARGE},
        {'K', TOK_ALPHA_LARGE},
        {'L', TOK_ALPHA_LARGE},
        {'M', TOK_ALPHA_LARGE},
        {'N', TOK_ALPHA_LARGE},
        {'O', TOK_ALPHA_LARGE},
        {'P', TOK_ALPHA_LARGE},
        {'Q', TOK_ALPHA_LARGE},
        {'R', TOK_ALPHA_LARGE},
        {'S', TOK_ALPHA_LARGE},
        {'T', TOK_ALPHA_LARGE},
        {'U', TOK_ALPHA_LARGE},
        {'V', TOK_ALPHA_LARGE},
        {'W', TOK_ALPHA_LARGE},
        {'X', TOK_ALPHA_LARGE},
        {'Y', TOK_ALPHA_LARGE},
        {'Z', TOK_ALPHA_LARGE},

        {'.', TOK_PUNC},
        {',', TOK_PUNC},
        {':', TOK_PUNC},
        {'\'', TOK_PUNC},
        {'\"', TOK_PUNC},
        {';', TOK_PUNC},
        {'?', TOK_PUNC},
        {'!', TOK_PUNC},
        {'(', TOK_PUNC},
        {')', TOK_PUNC},

        {EOF, TOK_EOF}
    }
);

int main()
{
    for (auto it = ClassifierTable->begin(); it != ClassifierTable->end(); ++it)
      cout << it->first << " = " << it->second << endl;

   return 0;

}