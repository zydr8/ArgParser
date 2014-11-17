#include <iostream>
#include <sstream>
#include <algorithm>

#include "ArgParser.h"

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::find;

ArgParser::ArgParser(int argc, char *argv[])
{
    CollectCmdArgs(argc, argv);
}

ArgParser::~ArgParser()
{
    mArgs.clear();
}

void ArgParser::CollectCmdArgs(int nargs, char *args[])
{
    mArgs.clear();
    for (int i = 0; i < nargs; ++i)
    {
        if (GetArgumentForm(args[i]) == ArgumentForm::SHORT)
        {
            // Check if need to split combined args: -abc, etc
            if (isCombinedArgs(args[i]))
            {
                for (auto spltArg :
                    SplitCombinedArgs(string(args[i] + 1)))   // Skip initial '-'
                {
                    mArgs.push_back(spltArg);
                }

                continue;
            }
        }

        mArgs.push_back(args[i]);
    }
}

#ifdef _DEBUG
void ArgParser::PrintArgs() const
{
    for (auto arg : mArgs)
    {
        cout << arg << " : ";

        switch (GetArgumentForm(arg))
        {
            case ArgumentForm::LONG:
            {
                cout << "LONG";
                break;
            }
            case ArgumentForm::PARAMETER:
            {
                cout << "PARAMETER";
                break;
            }
            case ArgumentForm::SHORT:
            {
                cout << "SHORT";
                break;
            }
            default:
            {
                cout << "INVALID";
                break;
            }
        }

        cout << endl;
    }
}
#endif

const string ArgParser::GetArgString() const
{
    stringstream ss;

    for (string arg : mArgs)
    {
        ss << arg.c_str() << " ";
    }
    ss << "\n";

    return ss.str();
}

bool ArgParser::HasFlag(const string &flag) const
{
    return find(begin(mArgs), end(mArgs), flag) != end(mArgs);
}

 ArgParser::ArgumentForm ArgParser::GetArgumentForm(const string &arg) const
{
    ArgumentForm result(ArgumentForm::INVALID);

    if (isArgShortForm(arg))
    {
        result = ArgumentForm::SHORT;
    }
    else if (isArgLongForm(arg))
    {
        result = ArgumentForm::LONG;
    }
    else if (isArgParameter(arg))
    {
        result = ArgumentForm::PARAMETER;
    }

    return result;
}

 bool ArgParser::isArgShortForm(const string &arg) const
 {
     return (arg[0] == '-') &&
         (arg[1] != '-');
 }

 bool ArgParser::isArgLongForm(const string &arg) const
 {
     return (arg[0] == '-') &&
         (arg[1] == '-');
 }

 bool ArgParser::isArgParameter(const string &arg) const
 {
     return (arg[0] != '-') &&
         (arg[1] != '-');
 }

 bool ArgParser::isCombinedArgs(const string &arg) const
 {
     // We already know arg form is SHORT
     return (arg.length() >= 3);
 }

 vector<string> ArgParser::SplitCombinedArgs(const string &args) const
 {
     vector<string> result;

     for (char arg : args)
     {
         // No clue why i can't initialize a std::string with a single char...
         string s("-");
         s.push_back(arg);

         result.push_back(s);
     }

     return result;
 }