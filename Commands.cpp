#include "Server.hpp"
#include "Client.hpp"

void Server::quit(int _socket) {
    deleteCommand(2);
    close(_socket);
    mapa[_socket]->setnickCheckMinus();
    mapa[_socket]->setpassCheckMinus();
    mapa[_socket]->setuserCheckMinus();
    std::cout << mapa[_socket]->getNickName() << ": disconnected\n";
    mapa[_socket]->setOfflineOnlineMinus();
    allClients--;
}


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

void Server::error(int error, int _socket, int iterator) {
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
    if (error == 433)
        msg += "433 " + commandClient[iterator] + " :Nickname is already in use";
    if (error == 461)
        msg += "461 " + mapa[_socket]->getNickName() + " :Not enough parameters";
    if (error == 409)
        msg += "409 " + mapa[_socket]->getNickName() + " :No origin specified";
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
                writeCommandClient(q, _socket);
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
    writeCommandClient(q, _socket);
    strcpy(str, msg.c_str());
    send (_socket, str, strlen(str), 0);
    deleteCommand(100);
}

int Server::pass(int _socket, int iterator) {
    if (checkPassword(commandClient[++iterator])){
        writeCommandClient(idClient + 1, _socket);
        mapa[_socket]->setpassCheckPlus();
    }
    iterator += 2;
    deleteCommand(iterator);
    return (iterator);
}

int Server::user(int _socket, int iterator) {
    int i = 0;
    i = iterator;
    while (commandClient[i] != "\n"){
        i++;
    }
    if (i < 5){
        error(461, _socket, 0);
        deleteCommand(i);
        return (0);
    }
    mapa[_socket]->setUserName(commandClient[++iterator]);
    mapa[_socket]->setzvezda(commandClient[++iterator]);
    mapa[_socket]->setHostName(commandClient[++iterator]);
    iterator++;
    while (commandClient[iterator] != "\n"){
        mapa[_socket]->setRealname(commandClient[iterator]);
        iterator++;
    }
    if (commandClient[iterator] == "\n")
        iterator++;
    else
        iterator += 2;
    writeCommandClient(idClient + 1, _socket);
    mapa[_socket]->setuserCheckPlus();
    deleteCommand(iterator);
    return (iterator);
}

int Server::nick(int _socket, int iterator) {
    if (checkNickClients(iterator)){
        mapa[_socket]->setNickName(commandClient[++iterator]);
        writeCommandClient(idClient + 1, _socket);
        mapa[_socket]->setnickCheckPlus();
        iterator += 2;
        deleteCommand(iterator);
        return (iterator);
    }
    error(433, _socket, iterator + 1);
    deleteCommand(10);
    return (iterator);
}

void Server::allowedCharacterJoin(int _socket) {
    int i = 0;
	while (str[i] != '\n'){
		if (str[i] != '#' && str[i] != '&' && str[i] != '+' && str[i] != '!')
			i++;
		else{
			 if (str[i - 1] == ' '){
            join(_socket);
            writeCommandClient(idClient + 1, _socket);
			break ;
        	}
        	else
        	    error(403, _socket, 0);
		}
	}
	if (str[i] == '\n')
		error(403, _socket, 0);
    deleteCommand(i);
    return;
}

void Server::allowedCharacterPrivmsg(int _socket) {
    int i = 0;
    while (str[i] != '#' || str[i] != '&' || str[i] != '+' || str[i] != '!') {
        if (str[i] == '\n'){
            privmsgClient(_socket);
            deleteCommand(i);
            return;
        }
        i++;
    }
    if (str[i] == '#' || str[i] == '&' || str[i] == '+' || str[i] == '!'){
        if (str[i - 1] == ' ')
            privmsgChannel(i, _socket);
        else
            error(403, _socket, 0);
    }
    deleteCommand(i);
    return;
}

void Server::ping(int _socket) {
    int i = 1;
    char str[BUFFER_SIZE];
    std::string msg;
    if (commandClient[i] == "")
        error(409, _socket, 0);
    msg = ":IRC PONG " + commandClient[i] + '\n';
    strcpy(str, msg.c_str());
    send(_socket, str, strlen(str), 0);
    writeCommandClient(idClient + 1, _socket);
    deleteCommand(10);
}

void Server::pingServer(int _socket)
{
    std::string msg;
    char str[BUFFER_SIZE];
    if (mapa[_socket]->getflagCheckPingPong() == 1){
        close(_socket);
        mapa[_socket]->minusFlagCheckPingPong();
        std::cout << mapa[_socket]->getNickName() << ": disconnected\n";
        mapa[_socket]->nullCheckPing();
        mapa[_socket]->setOfflineOnlineMinus();
        mapa[_socket]->setnickCheckMinus();
        mapa[_socket]->setpassCheckMinus();
        mapa[_socket]->setuserCheckMinus();
    }
    else{
        mapa[_socket]->plusFlagCheckPingPong();
        msg += "PING ircserv\n";
        strcpy(str, msg.c_str());
        send(_socket, str, strlen(str), 0);
        mapa[_socket]->nullCheckPing();
    }
}

void Server::pong(int _socket) {
    int i = 1;
    if (commandClient[i] == "ircserv"){
        mapa[_socket]->minusFlagCheckPingPong();
        writeCommandClient(idClient, _socket);
        deleteCommand(10);
        return ;
    }
}