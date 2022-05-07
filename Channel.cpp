#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel(): numClient(0){}

void Channel::setChannel(std::string nameChannel) {
    this->Channels = nameChannel;
}

void Channel::setClients(int _socketClient) {
    this->clients[numClient] = _socketClient;
    this->numClient++;
}

int Channel::socketClientForChannel(int i){return (this->clients[i]);}

int Channel::getNumClient(){return (this->numClient);}

void Channel::setPassword(std::string passwordChannel) {
    this->Password = passwordChannel;
}

std::string Channel::getPassword(){return (this->Password);}

void Channel::setKickClient(int i) {
    this->clients[i] = -1;
}

void Channel::setAdminChannel(int _socketAdmin) {
    this->adminChannel = _socketAdmin;
}

int Channel::getAdminChannel(){return (this->adminChannel);}

std::string Channel::getChannel() {
    return (this->Channels);
}

Channel::~Channel(){}

void Server::join(int _socket) {
    std::string msg;
    char str[BUFFER_SIZE];
    int i = 1;
    chann = chan.find(commandClient[i]);
    if (chann != chan.end()){
       if (commandClient[2] == chan[commandClient[i]]->getPassword()){
           chan[commandClient[i]]->setClients(_socket);
           msg += ":" + mapa[_socket]->getNickName() + "!" + mapa[_socket]->getUserName() + "@" + mapa[_socket]->getIP() + " ";
           i = 0;
           while (!commandClient[i].empty()){
               msg += commandClient[i] + " ";
               i++;
               if (i == 2)
                   msg += ": ";
           }
           strcpy(str, msg.c_str());
           send(chan[commandClient[1]]->getAdminChannel(), str, strlen(str), 0);
           error(331, _socket, 0);
           error(353, _socket, 0);
           error(366, _socket, 0);
           return;
       }
        else{
           error(401, _socket, 0);
        }
    }
    else if (numberChannelPasswordChannel >= 0){
        chan.insert(std::make_pair(commandClient[i], new Channel()));
        chan[commandClient[i]]->setChannel(commandClient[i]);
        mapa[_socket]->setMyChannel(commandClient[i]);
        chan[commandClient[i]]->setPassword(commandClient[i + 1]);
        chan[commandClient[i]]->setAdminChannel(_socket);
        chan[commandClient[i]]->setClients(_socket);
        numberChannelPasswordChannel++;
        error(331, _socket, 0);
        error(353, _socket, 0);
        error(366, _socket, 0);
        return;
    }
}

void Server::privmsgChannel(int i, int _socket) {
    i = 2;
    std::string msg;
    char str[BUFFER_SIZE];
    int q = 0;
    while (_socket != chan[commandClient[1]]->socketClientForChannel(q))
        q++;
    if (_socket == chan[commandClient[1]]->socketClientForChannel(q)){
        msg += ":" + mapa[_socket]->getNickName() + "!" + chan[commandClient[1]]->getChannel() + "@" + mapa[_socket]->getIP() + " ";
        i = 0;
        while (!commandClient[i].empty()){
            msg += commandClient[i] + " ";
            i++;
            if (i == 2)
                msg += ": ";
        }
        i = 0;
        strcpy(str, msg.c_str());
        while (i != chan[commandClient[1]]->getNumClient()){
            if (chan[commandClient[1]]->socketClientForChannel(i) == _socket){
                i++;
                continue ;
            }
            send(chan[commandClient[1]]->socketClientForChannel(i), str, strlen(str), 0);
            i++;
        }
    }
    else{
        error(401, _socket, 0);
    }
}

void Server::kick(int _socket) {
    int i = 1;
    std::string msg;
    char str[BUFFER_SIZE];
    int _socketKick;
    if (_socket != chan[commandClient[i]]->getAdminChannel())
        error(403, _socket, 0);
    chann = chan.find(commandClient[i]);
    if (chann != chan.end()){
        while (commandClient[2] != mapa[new_socket[i]]->getNickName())
            i++;
        if (commandClient[2] == mapa[new_socket[i]]->getNickName()){
            _socketKick = new_socket[i];
            i = 0;
            while (_socketKick != chan[commandClient[1]]->socketClientForChannel(i))
                i++;
            if (_socketKick == chan[commandClient[1]]->socketClientForChannel(i))
                chan[commandClient[1]]->setKickClient(i);
            else{
                error(401, _socket, 0);
                return;
            }
        }
        msg += ":" + mapa[_socket]->getNickName() + "!" + mapa[_socket]->getUserName() + "@" + mapa[_socket]->getIP() + " ";
        i = 0;
        while (!commandClient[i].empty()){
            msg += commandClient[i];
            i++;
        }
        strcpy(str, msg.c_str());
        send(_socket, str, strlen(str), 0);
        send(_socketKick, str, strlen(str), 0);
        deleteCommand(i);
        return;
    }
}