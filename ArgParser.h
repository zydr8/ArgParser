/*
    ArgParser

    Parses the command-line and serves up a vector of tokenized
    command-line arguments.

    TODO: Consider rename, CmdLnParser maybe.
*/

#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__

#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class ArgParser
{
    enum class ArgumentForm
    {
        SHORT = 0,
        LONG,
        PARAMETER,
        INVALID
    };

    public:
        explicit ArgParser(int argc, char* argv[]);
        ~ArgParser();

        const vector<string>& GetArgs() const { return mArgs; }
        const string GetArgString() const;

        bool HasFlag(const string &flag) const;


#ifdef _DEBUG
        void PrintArgs() const;
#endif


    private:
        void CollectCmdArgs(int nargs, char *args[]);
        ArgumentForm GetArgumentForm(const string &arg) const;

        bool isArgShortForm(const string &arg) const;
        bool isArgLongForm(const string &arg) const;
        bool isArgParameter(const string &arg) const;

        bool isCombinedArgs(const string &arg) const;

        vector<string> SplitCombinedArgs(const string &args) const;

        vector<string> mArgs;
    
    // Singleton Implementation
    private: 
        ArgParser(const ArgParser &) { }
        const ArgParser &operator=(const ArgParser &) { }
};

#endif