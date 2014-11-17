#include <iostream>
#include <string>

#include "ArgParser.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

void PromptContinue()
{
    cout << "\nPress any key to continue...\n";
    cin.get();
}

int main(int argc, char *argv[])
{
    ArgParser argParser(argc, argv);

    cout << argParser.GetArgString();
    cout << endl;

    argParser.PrintArgs();
    cout << endl;

    if (argParser.HasFlag("-Q"))
        cout << "Flag \"Q\" found!" << endl;

    if (argParser.HasFlag("asdf"))
        cout << "You should not see this..." << endl;

    PromptContinue();
    
    return EXIT_SUCCESS;
}