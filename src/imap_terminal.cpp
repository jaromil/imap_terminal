#include "./imap_terminal.h"
#include "./utils.h"
#include <iostream>

using namespace std;

namespace imap_terminal
{
    CImapTerminal::CImapTerminal(
        const std::string& username,
        const std::string& password,
        const std::string& host,
        const std::string& port,
        bool ssl) : 
        CImapSession(username, password, host, port, ssl)
    {
        __run();
    }

    CImapTerminal::~CImapTerminal()
    {
    
    }

    std::string CImapTerminal::__readLine() const
    {
        cout << host() << "$ ";

        std::string line;
        getline(cin, line);

        return line;
    }

    std::vector<std::string> CImapTerminal::__parseLine(const std::string& line) const
    {
        return CUtils::cmdline(line);
    }

    bool CImapTerminal::__executeLine(const std::vector<std::string>& line)
    {
        if (line[0] == "exit")
        {
            return false;
        }
        else if (line[0] == "pwd")
        {
            cout << pwd() << endl;
        }
        else if (line[0] == "ls")
        {
            if (line.size() == 2)
            {
                cout << ls(line[1]) << endl;
            }
            else
            {
                cout << ls() << endl;
            }
        }
        else if (line[0] == "cd")
        {
            if (line.size() == 2)
            {
                cout << cd(line[1]) << endl;
            }
            else
            {
                cout << cd() << endl;
            }
        }
        else if (line[0] == "whoami")
        {
            cout << whoami() << endl;
        }
        
        return true;
    }

    void CImapTerminal::__run()
    {
        while (1)
        {
            string line = __readLine();
            vector<string> tokens = __parseLine(line);

            if (tokens.size() == 0)
            {
                continue;
            }

            if (!__executeLine(tokens))
            {
                break;
            }
        }
    }
}