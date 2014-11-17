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
#include <cassert>

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
        
        // Static reference style singleton implementation
        // http://stackoverflow.com/questions/270947/can-any-one-provide-me-a-sample-of-singleton-in-c/271104#271104
        static ArgParser &Instance()
        {
            static ArgParser instance;
            return instance;
        }
        
        ~ArgParser();

        void Parse(int nargs, char *args[]);

        const vector<string>& GetArgs() const { return mArgs; }
        const string GetArgString() const;

        bool HasFlag(const string &flag) const;


#ifdef _DEBUG
        void PrintArgs() const;
#endif

    private:
        ArgumentForm GetArgumentForm(const string &arg) const;

        bool isArgShortForm(const string &arg) const;
        bool isArgLongForm(const string &arg) const;
        bool isArgParameter(const string &arg) const;

        bool isCombinedArgs(const string &arg) const;

        vector<string> SplitCombinedArgs(const string &args) const;

        vector<string> mArgs;
    
    // Singleton Implementation
    private: 
        ArgParser() { }
        ArgParser(const ArgParser &);
        ArgParser &operator=(const ArgParser &);
};

#endif