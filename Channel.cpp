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

void Channel::setAdminChannel(std::string name) {
    this->adminChannel = name;
}

std::string Channel::getChannel() {
    return (this->Channels);
}

Channel::~Channel(){}

void Server::join(int _socket) {
    int i = 1;
    chann = chan.find(commandClient[i]);
    if (chann != chan.end()){
        chan[commandClient[i]]->setClients(_socket);
        std::cout << mapa[_socket]->getNickName() << " added to channel: " << chan[commandClient[i]]->getChannel() << std::endl;
        return;
    }
    else if (numberChannelPasswordChannel >= 0){
        chan.insert(std::make_pair(commandClient[i], new Channel()));
        chan[commandClient[i]]->setChannel(commandClient[i]);
        chan[commandClient[i]]->setPassword(commandClient[i + 1]);
        chan[commandClient[i]]->setAdminChannel(mapa[_socket]->getNickName());
        chan[commandClient[i]]->setClients(_socket);
        std::cout << "Channel created. Admin: " + mapa[_socket]->getNickName() << std::endl;
        numberChannelPasswordChannel++;
        return;
    }
}

void Server::privmsgChannel(char *str, int i) {
    i = 3;
    std::string msg[BUFFER_SIZE];
    
    // msg += commandClient[i];
    // strcpy(mot, msg->c_str());
    while (!commandClient[i].empty()){
        msg += to_string(commandClient[i]);
        i++;
    }
    i = 0;
    while (i != chan[commandClient[1]]->getNumClient()){
        send(chan[commandClient[1]]->socketClientForChannel(i), , strlen(buffer), 0);
        i++;
    }
}