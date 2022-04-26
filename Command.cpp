#include "Command.hpp"

Server serv;
Client cl;

Command::Command(){}

bool Command::checkCommand(char *str) {
    int i = 0;
    int q = 0;
    int j = 0;
    std::string av0[7];
    // std::string av1;
    
    // while (str[q] != ' ')
    // {
    //     av0 += str[q];
    //     q++;
    // }
    // q++;
    // i++;
    // while (str[q] != '\n')
    // {
    //     av1 += str[q];
    //     q++;
    // }
    while (str[q] != '\n')
    {
        while (str[q] != ' ')
        {
            if ( str[q] == '\n' || str[q] == '\r')
                break ;
            if (str[q] == ':')
                q++;
            av0[i] += str[q];
            q++;
        }
        av0[i] += '\n';
        i++;
        if (str[q] == '\n')
            break;
        q++;
        continue;
    }
    if (av0[0] == "PASS")
    {
        if (serv.checkPassword(av0[0]) == true)
            return (true);
        return (false);
    }
    else if (av0[0] == "NICK"){cl.getNickName(av0[0]);}
    return (false);
}


Command::~Command() {}