#include <iostream>
#include <string>
#include "./REPL/REPL.h"

using namespace std;

int main()
{
    REPL *repl = new REPL();

    while(true)
    {
        string *input = new string();
        cout << "MLi> ";
        getline(cin, *input);

        repl->ReadLine(input);

        cout << "Ans: " << *(repl->getAnswer()->value) << endl;
        cout << endl;
    }

    return 0;
}