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
        i++;
        commandClient[i] = '\n';
        i++;
        if (str[q] == '\n')
            break ;
        q++;
        if (!str[q])
            break ;
    }
    return (i);
}

void Server::writeCommandClient(int idClient, int q, int _socket)
{
    int i = 0;
    std::cout << "Client #" << idClient << " ";
    while (commandClient[i] == "")
        i++;
    std::cout << "<" << commandClient[i] << "> ";
    i++;
    while (commandClient[i] != "\n"){
        while (commandClient[i] == "")
            i++;
        std::cout << "<" << commandClient[i] << "> ";
                 i++;
    }
    std::cout << std::endl;
}

bool Server::checkCommand(char *str, int _socket, int idClient) {
    int flag = 0;
    int q = 0;
    int i = 0;
    i = splitCommand(str);
    q = idClient + 1;
    flag = i;
    i = 0;
    while (mapa[_socket]->getOffineOnline() != 1){
        if (commandClient[i] == "PASS"){
            if (checkPassword(commandClient[++i])){
                flag++;
                writeCommandClient(q, i, _socket);
                mapa[_socket]->setpassCheck();
            }
            deleteCommand();
            if (commandClient[i + 2] == "NICK" || commandClient[i + 2] == "USER")
                i += 2;
            else{
                return (false);
            }
        }
        if (commandClient[i] == "USER"){
            mapa[_socket]->setUserName(commandClient[++i]);
            mapa[_socket]->setzvezda(commandClient[++i]);
            mapa[_socket]->setHostName(commandClient[++i]);
            mapa[_socket]->setRealname(commandClient[++i]);
            writeCommandClient(q, i, _socket);
            mapa[_socket]->setuserCheck();
            deleteCommand();
            if (commandClient[i + 2] == "PASS" || commandClient[i + 2] == "NICK"){
                i += 2;
                continue ;
            }
            else{
                return (false);
            }
        }
        if (commandClient[i] == "NICK"){
            mapa[_socket]->setNickName(commandClient[++i]);
            writeCommandClient(q, i, _socket);
            mapa[_socket]->setnickCheck();
            deleteCommand();
            if (commandClient[i] == "PASS" || commandClient[i] == "USER")
                continue ;
            else{
                return (false);
            }
        }
        else{
            error(451, _socket);
        }
    }
    if (commandClient[i] == "QUIT"){
        quit(_socket);
        std::cout << mapa[_socket]->getNickName() << ": disconnected\n";
        mapa[_socket]->setOfflineOnlineMinus();
        allClients--;
    }
    if (commandClient[i] == "JOIN"){
        i = 0;
        while (str[i] != '#'){
            if (str[i] == '\n')
                break ;
            i++;
        }
        if (str[i] == '#')
            join(_socket);
        else
            error(403, _socket);
        deleteCommand();
    }
    if (commandClient[i] == "PRIVMSG") {
        int i = 0;
        while (str[i] != '#') {
            if (str[i] == '\n')
                break ;
            i++;
        }
        if (str[i] == '#')
            privmsgChannel(str, i);
    }
    return (false);
}

void Server::quit(int _socket) {deleteCommand();close(_socket);}


void Server::deleteCommand() {
    int i = 0;
    while (commandClient[i] != "\n"){
        commandClient[i] = "";
        i++;
    }
    commandClient[i] = "";
}

void Server::error(int error, int _socket) {
    std::string msg[BUFFER_SIZE];
    char *str;
//    if (error == 451)
//        msg += ":IRC 451 :You have not registered\n";
//    if (error == 403)
//        msg += ":IRC 403 " + mapa[_socket]->getNickName() + " " + commandClient[1] + " :No such channel\n";
    strcpy(str, msg->c_str());
    send(_socket, str, strlen(str), 0);
}