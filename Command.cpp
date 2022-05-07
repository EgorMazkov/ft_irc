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
    if (mapa[_socket]->getnickCheck() == 1)
        std::cout << "nick: " << mapa[_socket]->getNickName() << " ";
    else
        std::cout << "Client #" << idClient << " ";
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
        ison(_socket);
        deleteCommand(100);
        return (false);
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
        return (false);
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
        return (false);
    }
    if (commandClient[i] == "PRIVMSG") {
        int i = 0;
        while (str[i] != '#' || str[i] != '&' || str[i] != '+' || str[i] != '!') {
            if (str[i] == '\n'){
                privmsgClient(_socket);
                deleteCommand(i);
                return (false);
            }
            i++;
        }
        if (str[i] == '#' || str[i] == '&' || str[i] == '+' || str[i] == '!'){
            if (str[i - 1] == ' ')
                privmsgChannel(str, i, _socket);
            else
                error(403, _socket);
        }
        deleteCommand(i);
        return (false);
    }
    if (commandClient[i] == "KICK"){
        kick(_socket);
        return (false);
    }
    error(421, _socket);
    writeCommandClient(i, q, _socket);
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
    int i = 0;
    char str[BUFFER_SIZE];
    msg = ":IRC ";
   if (error == 451)
       msg += "451 :You have not registered";
   if (error == 403)
       msg += "403 " + mapa[_socket]->getNickName() + " " + commandClient[1] + " :No such channel";
   if (error == 482)
       msg += "451 " +mapa[_socket]->getNickName() + ":You're not channel operator";
   if (error == 401)
       msg += "401 " + mapa[_socket]->getNickName() + chan[commandClient[1]]->getChannel() + " :No such nick/channel";
   if (error == 421){
       msg += "421 " + mapa[_socket]->getNickName() + " ";
       while (!commandClient[i].empty()){
        if (commandClient[i] != "\n")
            msg += commandClient[i++] + " ";
        else
            break;
       }
       msg += ":Unknown command";
   }
   if (error == 331){
       msg += "331 " + mapa[_socket]->getNickName() + chan[commandClient[1]]->getChannel() + " :No topic is set";
   }
    if (error == 353) {
        msg += "353 " + mapa[_socket]->getNickName() + "=" + chan[commandClient[1]]->getChannel() + " @";
        while (i != chan[commandClient[1]]->getNumClient()){
            msg += mapa[chan[commandClient[1]]->socketClientForChannel(i)]->getNickName() + " ";
            i++;
        }
    }
    if (error == 366)
        msg += "366 " + mapa[_socket]->getNickName() + chan[commandClient[1]]->getChannel() + " :End of /Names list";
   msg += '\n';
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

void Server::ison(int _socket) {
    std::string msg;
    char *str;
    int i = 0;
    int q = 1;
    int checkClients = 0;
    msg = ":IRC 303 " + mapa[_socket]->getNickName() + " :";
    while (new_socket[i] != -1){
        if (mapa[new_socket[i]]->getNickName() == commandClient[q] && mapa[new_socket[i]]->getOffineOnline() == 1){
            msg += mapa[new_socket[i]]->getNickName() + " ";
            checkClients = 1;
        }
        i++;
        if (checkClients == 1 && commandClient[q + 1] != "\n"){
            q++;
            i = 0;
            checkClients = 0;
            continue;
        }
    }
    msg += "\n";
    writeCommandClient(q, i, _socket);
    strcpy(str, msg.c_str());
    send (_socket, str, strlen(str), 0);
}