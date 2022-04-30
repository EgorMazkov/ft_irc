#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"

Channel::Channel(){}

void Channel::setChannel(std::string nameChannel) {
    this->Channels = nameChannel;
}

void Channel::setClients(std::string _socketClient) {
    this->clients[numberClient] = _socketClient;
    numberClient++;
}

void Channel::setPassword(std::string passwordChannel) {
    this->Password = passwordChannel;
}

void Channel::setAdminChannel(std::string name) {
    this->adminChannel = name;
}

Channel::~Channel(){}

void Server::join(int _socket, std::string av0, std::string av1, std::string av2, int flag) {
    int i = 1;
    int q = 2;
    t1 = chan.find(av0);
    if (t1 != chan.end())
    {
        chan[av0]->setClients(mapa[_socket]->getNickName());
        std::cout << "Клиент добавлен\n";
        return;
    }
    else if (numberChannelPasswordChannel >= 0) {
        chan.insert(std::make_pair(av0, new Channel()));
        chan[av0]->setChannel(av0);
        chan[av0]->setPassword(av1);
        chan[av0]->setAdminChannel(mapa[_socket]->getNickName());
        chan[av0]->setClients(mapa[_socket]->getNickName());
        std::cout << "Канал создан\n";
        numberChannelPasswordChannel++;
        return;
    
    }
}