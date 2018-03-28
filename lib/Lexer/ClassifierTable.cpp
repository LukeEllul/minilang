#include <iostream>
#include <string>
#include <map>
#include "../Token.cpp"

using namespace std;

map<char, TokenType> *ClassifierTable = new map<char, TokenType>(
    {
        {'1', TOK_Number},
        {'2', TOK_Number}
    }
);

int main()
{
    // for (auto it = ClassifierTable->begin(); it != ClassifierTable->end(); ++it)
    //   cout << it->first << " = " << it->second << endl;

   return 0;

}