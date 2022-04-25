#include "Command.hpp"

Server serv;
Client cl;

Command::Command(){}

bool Command::checkCommand(char *str) {
    int i = 0;
    int q = 0;
    int j = 0;
    std::string av0;
    std::string av1;
    
    while (str[q] != ' ')
    {
        av0 += str[q];
        q++;
    }
    q++;
    i++;
    while (str[q] != '\n')
    {
        av1 += str[q];
        q++;
    }
    std::cout << "<" << av0 << "> <" << av1 << ">" << std::endl;
    if (av0 == "PASS")
    {
        if (serv.checkPassword(av1) == true)
            return (true);
        return (false);
    }
    if (av0 == "NICK")
        cl.getNickName(av1);
    return (false);
}


Command::~Command() {}