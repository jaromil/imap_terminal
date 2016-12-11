#include "./utils.h"
#include <regex>

using namespace std;

namespace imap_terminal
{
    vector<string> CUtils::tokenize(string src, string delimiters)
    {
        vector<string> tokens;
        regex r(string("[^") + delimiters + string("]+"));
        smatch sm;
        while (regex_search(src, sm, r))
        {
            tokens.push_back(sm.str());
            src = sm.suffix();
        }

        return tokens;
    }

    std::vector<std::string> CUtils::cmdline(std::string src, std::string delimiters, string grouping)
    {
        vector<string> tokens;
        regex r(string(grouping) + "[^" + string(grouping) + "]*" + string(grouping));
        smatch sm;
        if (regex_search(src, sm, r))
        {
            if (sm.prefix().length() > 0)
            {
                tokens = tokenize(sm.prefix(), delimiters);
            }

            tokens.push_back(sm.str().substr(1,sm.str().length() - 2));

            if (sm.suffix().length() > 0)
            {
                vector<string> moreTokens = cmdline(sm.suffix(), delimiters, grouping);
                tokens.insert(tokens.end(), moreTokens.begin(), moreTokens.end());
            }
        }
        else
        {
            tokens = tokenize(src, delimiters);
        }
            
        return tokens;
        
    }

}