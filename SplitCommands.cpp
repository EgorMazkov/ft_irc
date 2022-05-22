#include "Server.hpp"

int Server::splitCommand(char *str) {
    int i = 0;
    int q = 0;
    while (str[q] != '\n')
    {
        while (str[q] != ' ')
        {
            if (str[q] == '\r' || str[q] == ':')
                q++;
            if (str[q] == '\n' && !str[q + 1])
                break ;
            if (str[q] == '\n' && str[q + 1])
            {
                q++;
                i++;
                commandClient[i] = '\n';
                i++;
                continue ;
            }
            commandClient[i] += str[q];
            q++;
        }
        if (str[q] == ' ')
        {
            while (str[q] == ' ')
                q++;
            i++;
            continue ;
        }
        if (commandClient[i] == "")
            commandClient[i] = '\n';
        else{
            i++;
            commandClient[i] = '\n';
        }
        if (str[q] == '\n')
            break ;
        q++;
        if (!str[q])
            break ;
    }
    if (str[q] == '\n' && commandClient[i - 1] != "\n")
        commandClient[i] = '\n';
    return (i);
}

void Server::writeCommandClient(int idClient, int _socket)
{
    int i = 0;
        std::cout << "Client" << " ";
    while (commandClient[i] == "")
        i++;
    std::cout << "<" << commandClient[i] << "> ";
    i++;
    while (commandClient[i] != "\n"){
        while (commandClient[i] == ""){
            i++;
            if (commandClient[i] == "\n"){
                std::cout << std::endl;
                return;
            }
        }
        if (commandClient[i] != "")
            std::cout << "<" << commandClient[i] << "> ";
        i++;
    }
    std::cout << std::endl;
}

void Server::checkCommand(char *str, int _socket, int idClient) {
    int i;
    
    mapa[_socket]->nullCheckPing();
    deleteCommand(1);
    i = splitCommand(str);
    i = 0;
    if (commandClient[i] == "ISON"){ison(_socket); return;}
    while (mapa[_socket]->getOffineOnline() != 1){
        if (commandClient[i] == "PASS"){i = pass(_socket, i);}
        if (commandClient[i] == "USER"){i = user(_socket, i);}
        if (commandClient[i] == "NICK"){i = nick(_socket, i);}
        if (!commandClient[i].empty()){
            error(421, _socket, 0);
            writeCommandClient(idClient + 1, _socket);
            deleteCommand(100);
        }
        return;
    }
    if (commandClient[i] == "QUIT"){quit(_socket); return;}
    if (commandClient[i] == "JOIN"){ allowedCharacterJoin(_socket);return;}
    if (commandClient[i] == "PRIVMSG") { allowedCharacterPrivmsg(_socket);return;}
    if (commandClient[i] == "KICK"){kick(_socket);return;}
    if (commandClient[i] == "PING"){ping(_socket); return;}
    if (commandClient[i] == "PONG"){pong(_socket); return;}
    error(421, _socket, 0);
    writeCommandClient(idClient + 1, _socket);
    deleteCommand(100);
    return;
}

