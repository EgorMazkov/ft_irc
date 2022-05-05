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
    deleteCommand(1);
    i = splitCommand(str);
    q = idClient + 1;
    flag = i;
    i = 0;
    if (commandClient[i] == "ISON"){
        deleteCommand(10);
    }
    while (mapa[_socket]->getOffineOnline() != 1){
        if (commandClient[i] == "PASS"){
            if (checkPassword(commandClient[++i])){
                flag++;
                writeCommandClient(q, i, _socket);
                mapa[_socket]->setpassCheckPlus();
            }
            i += 2;
            deleteCommand(i);
            if (commandClient[i] == "NICK" || commandClient[i] == "USER")
                ;
            else{
                return (false);
            }
        }
        if (commandClient[i] == "USER"){
            mapa[_socket]->setUserName(commandClient[++i]);
            mapa[_socket]->setzvezda(commandClient[++i]);
            mapa[_socket]->setHostName(commandClient[++i]);
            i++;
            while (commandClient[i] != "\n"){
                mapa[_socket]->setRealname(commandClient[i]);
                i++;
            }
            if (commandClient[i] == "\n")
                i++;
            else
                i += 2;
            writeCommandClient(q, i, _socket);
            mapa[_socket]->setuserCheckPlus();
            deleteCommand(i);
            if (commandClient[i] == "PASS" || commandClient[i] == "NICK"){
                continue ;
            }
            else{
                return (false);
            }
        }
        if (commandClient[i] == "NICK"){
            mapa[_socket]->setNickName(commandClient[++i]);
            writeCommandClient(q, i, _socket);
            mapa[_socket]->setnickCheckPlus();
            i += 2;
            deleteCommand(i);
            if (commandClient[i] == "PASS" || commandClient[i] == "USER")
                continue ;
            else{
                return (false);
            }
        }
        else{
            error(451, _socket);
            return (false);
        }
    }
    if (commandClient[i] == "QUIT"){
        quit(_socket);
        mapa[_socket]->setnickCheckMinus();
        mapa[_socket]->setpassCheckMinus();
        mapa[_socket]->setuserCheckMinus();
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
        {
            if (str[i - 1] == ' '){
                join(_socket);
                writeCommandClient(q, i, _socket);
            }
            else
                error(403, _socket);
        }
        else
            error(403, _socket);
        deleteCommand(i);
    }
    if (commandClient[i] == "PRIVMSG") {
        int i = 0;
        while (str[i] != '#') {
            if (str[i] == '\n'){
                privmsgClient(_socket);
                return (false);
            }
            i++;
        }
        if (str[i] == '#'){
            if (str[i - 1] == ' ')
                privmsgChannel(str, i, _socket);
            else
                error(403, _socket);
        }
        deleteCommand(i);
    }
    if (commandClient[i] == "KICK"){
        kick(_socket);
    }
    deleteCommand(100);
    return (false);
}

void Server::quit(int _socket) {deleteCommand(2);close(_socket);}


void Server::deleteCommand(int q) {
    int i = 0;
    if (commandClient[i] == "QUIT")
    {
        while (!commandClient[i].empty()){
            commandClient[i] = "";
            i++;
        }
        return ;
    }
    while (i != q - 1){
        commandClient[i] = "";
        i++;
    }
    commandClient[i] = "";
}

void Server::error(int error, int _socket) {
    std::string msg;
    char str[BUFFER_SIZE];
   if (error == 451)
       msg += ":IRC 451 :You have not registered\n";
   if (error == 403)
       msg += ":IRC 403 " + mapa[_socket]->getNickName() + " " + commandClient[1] + " :No such channel\n";
   if (error == 482)
       msg += ":IRC 451" +mapa[_socket]->getNickName() + ":You're not channel operator\n";
   if (error == 401)
       msg += ":IRC 401" + mapa[_socket]->getNickName() + chan[commandClient[1]]->getChannel() + " :No such nick/channel\n";
    strcpy(str, msg.c_str());
    send(_socket, str, strlen(str), 0);
    return ;
}

void Server::privmsgClient(int _socket) {
    std::string msg;
    char msg1[BUFFER_SIZE];
    int i = 0;
    int q = 1;
    while (i != allClients){
        if (mapa[new_socket[i]]->getNickName().compare(commandClient[q]) == 0){
            if (mapa[new_socket[i]]->getOffineOnline() == 1){
                msg += ":" + mapa[_socket]->getNickName() + "!" + mapa[_socket]->getUserName() + "@" + mapa[_socket]->getIP() + " ";
                q = 0;
                while (!commandClient[q].empty()){
                    msg += commandClient[q] + " ";
                    q++;
                    if (q == 2)
                        msg += ": ";
                }
                strcpy(msg1, msg.c_str());
                send(new_socket[i], msg1, strlen(msg1), 1);
                writeCommandClient(q, i, _socket);
                deleteCommand(q);
                return ;
            }
            else {
                
            }
        }
        i++;
    }
}