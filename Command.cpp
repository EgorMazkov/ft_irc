#include "Command.hpp"

Command::Command(){}

bool Command::checkCommand(char *str, int _socket, Server serv) {
    int i = 0;
    int q = 0;
    int j = 0;
    std::string av0[7];
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
        // av0[i] += '\n';
        i++;
        if (str[q] == '\n')
            break;
        q++;
        continue;
    }
    if (av0[0] == "PASS")
    {
        if (serv.checkPassword(av0[1]) == true)
        {
             serv.mapa[_socket]->setpassCheck();
            // cl.setPassNickUser();
            return (true);
        }
        return (false);
    }
    if (av0[0] == "NICK"){
         serv.mapa[_socket]->setnickCheck();
         serv.mapa[_socket]->setNickName(av0[0]);
    }
//    if (av[0] == "USER")
//    {
//
//    }
    return (false);
}


Command::~Command() {}